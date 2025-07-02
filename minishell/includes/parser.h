/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:41:28 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/18 18:59:59 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_msh	t_msh;

/*process_arguments_1.c*/
char	*extract_command(t_msh *shell, char *segment);
int		count_arguments_parser(char *s);

/*process_arguments_2.c*/
int		check_null_args(char *s);
char	*change_null_args(char *s, t_cmd *cmd);
char	**extract_arguments(t_msh *shell, char *segment, t_cmd *command);

/*process_arguments_3.c*/
int		skip_spaces(const char *s, int i);
int		skip_token(const char *s, int i);
int		get_operator_length(int rtype);
int		skip_initial_redirections(const char *s, int i);

/*process_arguments_utils.c*/
char	*quit_null_space(char *s, int index);
char	*quit_null(char *s, int index);

/*variable_braced.c*/
int		parse_braced(const char *line, int *colon, int *end);
char	*expand_braced_substring(t_msh *msh, char *line);
char	*process_braced_value(char *value, int offset, char *suffix);
char	*compare_variable_name(t_msh *msh, char *line, char *nameVar);
char	*replace_variable_in_line(char *line, char *var);

/*variable_detection.c*/
int		has_variable(const char *s);
int		check_variable_and_digit(const char *s);
int		is_digit_special(int c);
char	*extract_variable_name(char *line);
int		find_next_dollar(const char *s, int start);

/*variable_env.c*/
int		compare_env_variable_name(const char *s1, const char *s2);
char	*extract_env_value(const char *envVar);
char	*split_variable_reminder(char *line, int index, t_cmd *cmd);
char	*replace_special_value_helper(char *s, int i, int error_value);

/*variable_expansion.c*/
int		needs_home_expansion(const char *s);
char	*expand_home_directory(char *s);
char	*expand_translation(t_msh *msh, char *line);
int		detect_translation(const char *line, int *end);
char	*replace_special_value(char *s, int error_value);

/*variable_processing.c*/
char	*quit_variable_and_digit(char *s);
int		is_literal_dollar(const char *line);
void	init_flags(t_cmd *cmd);
int		special_char_ck(char c);
char	*join_special(const char *s1, const char *s2);

/*variable_substitution.c*/
char	*substitute_variables(t_msh *msh, t_cmd *cmd, char *s,
			char **varReminder);
char	*substitute_variable_value(t_msh *msh, t_cmd *cmd, char *line,
			char **varReminder);
void	handle_special_case(t_cmd *cmd, char **s, char **varReminder);
char	*handle_special_variable(t_msh *msh, t_cmd *cmd, char *line,
			char **varReminder);
int		handle_special_chars(char *line, int i, char **varReminder, t_cmd *cmd);

/*p_pipes_redir.c*/
int		process_redirection(const char *s, int i, int *count);
int		count_redirections(const char *s);
char	*extract_redirect_token(char *s);
int		validate_redirection_syntax(char **segments, int index);

/*p_pipes_utils.c*/
char	**extract_pipe_segments(char *s, char **segments);
int		validate_pipe_segment(char *segment);

/*parse_pipes.c*/
int		count_pipes(const char *inputline, t_msh *msh);
char	**split_pipes(char *inputline, t_msh *msh);

/*parse_quotes.c*/
int		check_quotes_balance(const char *s, t_msh *shell);
int		get_next_quote(int i, char *str, char c);

/*parser_functions.c*/
void	setup_command_node(t_cmd *node, t_msh *shell, int cmd_idx);
t_cmd	*create_command_node(t_msh *shell, char *segment);
void	expand_command_arguments(t_msh *msh, t_cmd **command,
			char *var_reminder);
void	perform_expansion(t_msh *msh, t_cmd **command);
t_cmd	*get_last_command_node(t_cmd **cmd);

/*parser.c*/
int		validate_and_split_input(t_msh *shell, char *inputline,
			char ***segments);
int		parse_input_line(t_msh *shell, t_cmd **commandList, char *inputline);

#endif