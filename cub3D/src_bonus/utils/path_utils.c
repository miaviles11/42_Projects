/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:57:42 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:57:42 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* -------------------------------------------------------------------------- */
/*  Devuelve el directorio de `path` (sin el nombre del fichero)              */
/*  Ej.: "/foo/bar/map.cub"  ->  "/foo/bar"                                   */
/* -------------------------------------------------------------------------- */
char	*ft_dirname(const char *path)
{
	size_t	i;
	char	*dir;

	if (!path || !*path)
		return (ft_strdup("."));
	i = 0;
	while (path[i])
		++i;
	while (i && path[i - 1] != '/')
		--i;
	if (i == 0)
		return (ft_strdup("."));
	dir = (char *)malloc(i + 1);
	if (!dir)
		return (NULL);
	ft_memcpy(dir, path, i);
	dir[i] = '\0';
	return (dir);
}

/* -------------------------------------------------------------------------- */
/*  Une `dir` + "/" + `file`  →  string nuevo                                 */
/* -------------------------------------------------------------------------- */
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

char	*ft_path_parent(const char *dir)
{
	return (path_join(dir, ".."));
}

/* 0 = no existe, 1 = existe y es legible */
int	file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
