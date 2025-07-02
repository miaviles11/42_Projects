/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:23:48 by miaviles          #+#    #+#             */
/*   Updated: 2025/04/02 11:20:44 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>

typedef struct s_cmd	t_cmd;
typedef struct s_msh	t_msh;

/* exec_utils.c */
int		is_exit_command(t_msh *shell);
int		handle_exit_command(t_msh *shell, char **args, int code);

/*child_process.c - Gestiona la configuración y ejecución de procesos hijo*/
char	*find_executable(char *cmd);
char	**prepare_argv(t_cmd *cmd);
void	setup_child_process(t_msh *msh, t_cmd *cmd, int in_fd,
			int out_fd);
void	child_process(t_msh *msh, t_cmd *cmd, int input_fd, int output_fd);

/*exec_builtin.c - Implementa la ejecución de comandos builtin*/
void	execute_builtin_with_redirection(t_msh *msh, t_cmd *cmd, int out_fd);
int		exec_builtin(t_msh *msh, char **argv);
int		is_builtin(char *cmd_name);
void	execute_builtin(t_msh *msh, t_cmd *cmd);
void	exit_child(t_cmd *cmd);

/*exec_utils_builtin.c - Funciones auxiliares para comandos builtin*/
void	setup_builtin_args(t_msh *msh, t_cmd *cmd, char ***argv);
void	cleanup_builtin(int saved_out, int saved_err);

/*exec_utils.c - Utilidades generales para la ejecución de comandos*/
void	wait_for_children(void);
char	*check_command_path(char *cmd);
char	*search_in_path(char *cmd);
void	execute_last_cmd(t_msh *msh, t_cmd *cmd);
void	redir_only_child(t_msh *msh, t_cmd *cmd);

/*executor_heredoc.c - Manejo de redirecciones heredoc (<<)*/
void	read_here_doc_lines(char *delimiter);
void	consume_here_docs(char **args);

/*executor_pipe.c - Gestión de tuberías y comando conectados*/
void	process_cmd_with_pipe(t_msh *msh, t_cmd *cmd, int prev_pipe,
			int *pipe_fd);
void	setup_pipe_redirections(int prev_pipe, int *pipe_fd);
void	process_last_cmd(t_msh *msh, t_cmd *cmd, int prev_pipe);
void	setup_last_cmd_redirections(int prev_pipe);
void	execute_cmd_in_pipe(t_msh *msh, t_cmd *cmd);
void	wait_fg(t_msh *msh, pid_t pid, int background);
void	last_cmd_child(t_msh *msh, t_cmd *cmd, int prev_pipe);

/*executor.c - Funciones principales del ejecutor de comandos*/
void	exec_child(t_msh *msh, t_cmd *cmd, char *executable);
void	handle_command_execution(t_msh *msh, t_cmd *cmd, char *executable);
void	execute_single_command(t_msh *msh, t_cmd *cmd);
void	execute_pipeline(t_msh *msh);
void	execute_commands(t_msh *msh);

#endif