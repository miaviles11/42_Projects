/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:46:08 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/17 18:26:39 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_msh	t_msh;

/*builtins_utils_export.c*/
char	**ft_duplicate_env(char **env, int *len);
char	**ft_sort_env_array(char **sorted, int len);
char	**ft_split_sort_env(char **env);

/*builtins_utils.c*/
int		update_existing_env_var(t_msh *msh, const char *name,
			const char *value);
int		add_new_env_var(t_msh *msh, const char *name, const char *value);
int		set_env_var(t_msh *msh, const char *name, const char *value);
int		is_valid_identifier(const char *var);
char	**ft_split_sort_env(char **env);

/*ft_cd.c*/
int		minishell_cd(t_msh *msh, char **argv);

/*ft_echo.c*/
int		handle_no_newline(t_cmd *cmd, int *no_newline);
int		minishell_echo(t_msh *msh);

/*ft_pwd.c*/
int		minishell_pwd(t_msh *msh);

/*ft_exit.c*/
int		is_numeric(const char *str);
int		minishell_exit(t_msh *msh);

/*ft_env.c*/
int		minishell_env(t_msh *msh);

/*ft_export.c*/
int		minishell_export(t_msh *msh, char **argv);
void	update_env(t_msh *msh, const char *arg);
void	handle_no_equal(t_msh *msh, const char *arg);
void	print_sorted_env(char **sorted);
int		export_no_args(t_msh *msh);

/*ft_unset.c*/
int		minishell_unset(t_msh *msh, char **args);
void	remove_env_var(t_msh *msh, const char *key);

#endif