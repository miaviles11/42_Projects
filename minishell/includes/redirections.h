/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:18:01 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/10 12:18:01 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include <fcntl.h>

typedef struct s_cmd	t_cmd;
typedef struct s_msh	t_msh;

typedef struct s_idx
{
	size_t	*i;
	size_t	*j;
}	t_idx;

/*redirect_heredoc.c*/
void	read_here_doc_loop(const char *delimiter, int write_fd, int tty_fd);
void	read_here_doc_to_pipe(const char *delimiter, int write_fd);
void	setup_heredoc_pipe(int *heredoc_pipe, int *has_heredoc);

/* redir_utils.c */
int		is_redirect_operator(char c);
int		get_redirect_type(char *str);
int		find_first_redirect_index(char **args);
char	get_operator_for_type(int n);
int		find_next_redirect_operator_index(int i, char *str);

/* redir_utils2.c */
char	*preprocess_redirections(const char *line);
int		handle_quotes(t_idx *idx, char *out, const char *line, char *quote);
int		handle_double_redirections(t_idx *idx, char *out, const char *line);
int		handle_stderr_redirection(t_idx *idx, char *out, const char *line);
int		handle_single_redirection(t_idx *idx, char *out, const char *line);
void	*xmalloc(size_t size);

/*redirect.c*/
void	process_redirections(t_cmd *cmd);
void	handle_output_redirection(int redirType,
			t_cmd *command, char *filename);
void	handle_here_document(t_cmd *command, char *delimiter);
int		redirect_input_from_file(t_cmd *command, char *fileName, int argIndex);
char	**remove_argument_at_index(char **argumentList, int removalIndex);
char	**insert_argument_at_index(char **argList, char *newArg, int idx);
char	**keep_argument(char **arg, int j, char c);
int		count_arguments_redirections(char **args);
int		get_next_diff_op(int i, char *str);
char	*extract_redirect_token(char *s);
int		count_args(char **args);
void	read_here_doc(int write_fd, int tty_fd, char *delimiter);
void	init_here_doc(int p[2], int *tty_fd);
char	**get_filename(char **args, int index, char opChar, int offset);
void	apply_redirections(t_cmd *cmd, int heredoc_pipe[2]);
void	setup_heredocs_pre_scan(t_cmd *cmd, int heredoc_pipe[2], int *has_hd);
void	process_single_redirection(t_cmd *cmd, int *i,
			int heredoc_pipe[2]);

#endif