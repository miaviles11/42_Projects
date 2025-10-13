/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:24 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:24 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Return the directory part of `path` (without the filename).
** Example: "/foo/bar/map.cub" -> "/foo/bar"
*/
char	*ft_dirname(const char *path)
{
	size_t	i;
	char	*dir;

	if (!path || !*path)
		return (ft_strdup("."));
	i = 0;
	while (path[i])
		i++;
	while (i && path[i - 1] != '/')
		i--;
	if (i == 0)
		return (ft_strdup("."));
	dir = (char *)malloc(i + 1);
	if (!dir)
		return (NULL);
	ft_memcpy(dir, path, i);
	dir[i] = '\0';
	return (dir);
}

/*
** Join `dir` + "/" + `file` into a newly allocated string.
*/
char	*path_join(const char *dir, const char *file)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, file);
	free(tmp);
	return (joined);
}

/*
** Build the parent path of `dir` (i.e., dir + "/..").
*/
char	*ft_path_parent(const char *dir)
{
	return (path_join(dir, ".."));
}

/*
** Returns 1 if `path` exists and is readable, 0 otherwise.
*/
int	file_exists(const char *path)
{
	int	fd;

	if (!path || !*path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
