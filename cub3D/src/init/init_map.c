/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:57:27 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 14:57:27 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* dynamic grid growth ------------------------------------------------------ */
static int	grow_grid(char ***grid, int *cap)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * ((*cap * 2) + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while (i < *cap)
	{
		tmp[i] = (*grid)[i];
		i++;
	}
	free(*grid);
	*grid = tmp;
	*cap *= 2;
	return (0);
}

/* duplicate & store one line, stripping trailing newlines ------------------ */
static int	push_line(char *src, t_grid_ctx *ctx)
{
	char	*dup;
	char	*end;
	int		len;

	if (*(ctx->h) >= *(ctx->cap) && grow_grid(ctx->g, ctx->cap))
		return (-1);
	dup = ft_strdup(src);
	if (!dup)
		return (-1);
	end = dup + ft_strlen(dup) - 1;
	while (end >= dup && (*end == '\n' || *end == '\r'))
	{
		*end = '\0';
		end--;
	}
	(*(ctx->g))[*(ctx->h)] = dup;
	len = ft_strlen(dup);
	if (len > *(ctx->w))
		*(ctx->w) = len;
	*(ctx->h) += 1;
	return (0);
}

/* consume map lines; leaves *line at first non-map or NULL ----------------- */
static int	process_map_lines(int fd, t_grid_ctx *ctx, char **line)
{
	while (*line && is_map_line(*line))
	{
		if (push_line(*line, ctx))
		{
			free(*line);
			gnl_drain(fd);
			return (-1);
		}
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}

/* lee la sección de mapa y valida que no haya contenido tras el mapa ------- */
int	read_map(int fd, t_cub *cub, int *cap)
{
	char		*line;
	int			err;
	t_grid_ctx	ctx;

	err = 0;
	ctx.g = &cub->map.grid;
	ctx.h = &cub->map.h;
	ctx.cap = cap;
	ctx.w = &cub->map.w;
	if (skip_to_map(fd, &line))
		return (-1);
	if (process_map_lines(fd, &ctx, &line))
		return (-1);
	if (line)
	{
		if (!is_blank_line(line))
			err = -1;
		free(line);
		gnl_drain(fd);
	}
	return (err);
}

/* PUBLIC ------------------------------------------------------------------- */
int	init_map(t_cub *cub, const char *path)
{
	int	fd;
	int	cap;

	cap = 16;
	cub->map.grid = (char **)malloc(sizeof(char *) * (cap + 1));
	if (!cub->map.grid)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read_map(fd, cub, &cap))
	{
		close(fd);
		return (-1);
	}
	cub->map.grid[cub->map.h] = NULL;
	close(fd);
	return (normalize_map(&cub->map));
}
