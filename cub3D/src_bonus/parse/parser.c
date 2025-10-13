/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:25 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/08 22:00:41 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* store a duplicate into the list, stripping trailing newlines ------------- */
static int	store_line(t_list **lst, char *line)
{
	char	*dup;
	char	*end;

	dup = ft_strdup(line);
	if (!dup)
		return (-1);
	end = dup + ft_strlen(dup) - 1;
	while (end >= dup && (*end == '\n' || *end == '\r'))
	{
		*end = '\0';
		end--;
	}
	ft_lstadd_back(lst, ft_lstnew(dup));
	return (0);
}

/* read whole file ---------------------------------------------------------- */
static int	read_file(int fd, t_list **lst)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (store_line(lst, line))
		{
			free(line);
			gnl_drain(fd);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

/* process metadata and then initialize the map ----------------------------- */
static int	process_meta(t_cub *cub, t_list *node, const char *path)
{
	int	floor_set;
	int	ceil_set;

	floor_set = 0;
	ceil_set = 0;
	if (scan_header(cub, &node, &floor_set, &ceil_set))
		return (-1);
	if (validate_header_complete(cub, node != NULL, floor_set, ceil_set))
		return (-1);
	return (init_map(cub, path));
}

/* PUBLIC: parse entire scene file (.cub) ----------------------------------- */
int	parse_scene(t_cub *cub, const char *path)
{
	int		fd;
	t_list	*lst;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lst = NULL;
	if (read_file(fd, &lst) || process_meta(cub, lst, path) || check_map(cub)
		|| parse_doors(cub) || parse_sprites(cub))
	{
		ft_lstclear(&lst, free);
		gnl_drain(fd);
		close(fd);
		return (-1);
	}
	ft_lstclear(&lst, free);
	gnl_drain(fd);
	close(fd);
	return (0);
}
