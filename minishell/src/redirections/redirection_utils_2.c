/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:20:53 by carlsanc          #+#    #+#             */
/*   Updated: 2025/03/28 16:46:17 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**alloc_and_clamp(char **argList, int *idx, int *count)
{
	char	**newlist;

	*count = count_arguments_redirections(argList);
	if (*idx < 0)
		*idx = 0;
	if (*idx > *count)
		*idx = *count;
	newlist = malloc(sizeof(char *) * (*count + 2));
	if (!newlist)
		exit_error("Error de asignación en insert_argument_at_index", 1);
	return (newlist);
}

char	**insert_argument_at_index(char **argList, char *newArg, int idx)
{
	int		count;
	char	**newlist;
	int		i;
	int		j;

	newlist = alloc_and_clamp(argList, &idx, &count);
	i = 0;
	while (i < idx)
	{
		newlist[i] = argList[i];
		i++;
	}
	newlist[idx] = newArg;
	j = idx + 1;
	while (i < count)
	{
		newlist[j++] = argList[i++];
	}
	newlist[count + 1] = NULL;
	free(argList);
	return (newlist);
}

static int	get_skip(const char *str, char opChar)
{
	int	i;

	i = 0;
	if (str[i] == '2' && str[i + 1] == '>')
		i++;
	while (str[i] == opChar)
		i++;
	return (i);
}

static char	**insert_splits(char **args, int index, int i, int offset)
{
	int	k;
	int	next;

	k = offset;
	args = insert_argument_at_index(args,
			ft_substr(args[index], 0, i),
			index + k);
	k++;
	next = get_next_diff_op(i, args[index]);
	args = insert_argument_at_index(args,
			ft_substr(args[index], i, next - i),
			index + k);
	k++;
	if (args[index][next])
		args = insert_argument_at_index(args,
				ft_substr(args[index], next,
					ft_strlen(args[index]) - next),
				index + k);
	args = remove_argument_at_index(args, index);
	return (args);
}

char	**get_filename(char **args, int index, char opChar, int offset)
{
	int	i;

	i = get_skip(args[index], opChar);
	if (!args[index][i])
		return (args);
	if (i == 0)
		return (keep_argument(args, index, opChar));
	return (insert_splits(args, index, i, offset));
}
