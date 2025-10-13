/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:56 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 18:32:39 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_UTILS_H
# define PATH_UTILS_H

char	*ft_dirname(const char *path);
char	*path_join(const char *dir, const char *file);
char	*ft_path_parent(const char *dir);
int		file_exists(const char *path);

#endif
