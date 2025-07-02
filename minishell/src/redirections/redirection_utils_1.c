/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:48:13 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:48:13 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_output_redirection(int redirType, t_cmd *command, char *filename)
{
	int	fd;
	int	openflags;

	(void)command;
	if (redirType == 1 || redirType == 5)
		openflags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		openflags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(filename, openflags, 0644);
	if (fd == -1)
		exit_error("Error al abrir el archivo de salida", 44);
	if (redirType == 5 || redirType == 6)
	{
		if (dup2(fd, STDERR_FILENO) == -1)
			exit_error("Error al redirigir stderr", 45);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit_error("Error al redirigir stdout", 45);
	}
	free(filename);
	close(fd);
}

void	handle_here_document(t_cmd *command, char *delimiter)
{
	int	p[2];
	int	tty_fd;

	(void)command;
	init_here_doc(p, &tty_fd);
	read_here_doc(p[1], tty_fd, delimiter);
	close(tty_fd);
	close(p[1]);
	if (dup2(p[0], STDIN_FILENO) == -1)
		exit_error("Error al redirigir STDIN para here-document", 55);
	close(p[0]);
	free(delimiter);
}

int	redirect_input_from_file(t_cmd *command, char *fileName, int argIndex)
{
	int	filedescriptor;
	int	pipedescriptors[2];

	filedescriptor = open(fileName, O_RDONLY);
	if (filedescriptor == -1)
	{
		put_error("bash", fileName, "No such file or directory");
		if (pipe(pipedescriptors) == -1)
			exit_error("Error al crear pipe para redirección de entrada", 47);
		if (dup2(pipedescriptors[1], STDOUT_FILENO) == -1)
			exit_error("Error al redirigir salida, fallo de entrada", 50);
		if (close(pipedescriptors[0]) == -1
			|| close(pipedescriptors[1]) == -1)
			exit_error("Error al cerrar pipe para redirección", 51);
		while (command->arg[argIndex])
			command->arg = remove_argument_at_index(command->arg, argIndex);
		free(fileName);
		return (1);
	}
	else if (dup2(filedescriptor, STDIN_FILENO) == -1)
		exit_error("Error al redirigir entrada", 45);
	close(filedescriptor);
	free(fileName);
	return (0);
}

static char	**build_arg_list(char **args, int total, int rem)
{
	char	**new;
	int		i;
	int		j;

	new = malloc(sizeof(char *) * total);
	if (!new)
		exit_error("Error de asignación de memoria al remover argumento", 1);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (i != rem)
		{
			new[j] = args[i];
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	**remove_argument_at_index(char **argumentList, int removalIndex)
{
	int		totalargs;
	char	**newargumentlist;

	if (argumentList == NULL)
		return (NULL);
	totalargs = count_args(argumentList);
	if (removalIndex < 0 || removalIndex >= totalargs)
		return (argumentList);
	free(argumentList[removalIndex]);
	newargumentlist = build_arg_list(argumentList, totalargs, removalIndex);
	free(argumentList);
	return (newargumentlist);
}
