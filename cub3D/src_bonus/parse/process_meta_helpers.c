/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_meta_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:31:20 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/08 22:00:44 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

int	all_textures_set(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!cub->textures[i].path)
			return (0);
		i++;
	}
	return (1);
}

int	handle_color_line(int *dst, int *flag, char *s)
{
	if (*flag)
		return (-1);
	if (parse_color_line(dst, s))
		return (-1);
	*flag = 1;
	return (0);
}

/* Procesa una línea del header: texturas, F o C. Devuelve 0 ok, -1 error. */
int	handle_header_line(t_cub *cub, char *s,
	int *floor_set, int *ceil_set)
{
	if (!ft_strncmp(s, "NO", 2) || !ft_strncmp(s, "SO", 2)
		|| !ft_strncmp(s, "WE", 2) || !ft_strncmp(s, "EA", 2))
	{
		if (parse_texture_line(cub, s))
			return (-1);
		return (0);
	}
	if (*s == 'F' && (s[1] == ' ' || s[1] == '\t'))
	{
		if (handle_color_line(&cub->floor_color, floor_set, s))
			return (-1);
		return (0);
	}
	if (*s == 'C' && (s[1] == ' ' || s[1] == '\t'))
	{
		if (handle_color_line(&cub->ceil_color, ceil_set, s))
			return (-1);
		return (0);
	}
	if (*s != '\0')
		return (-1);
	return (0);
}

/* Recorre el header hasta el mapa. Devuelve 0 ok, -1 error. */
int	scan_header(t_cub *cub, t_list **node,
	int *floor_set, int *ceil_set)
{
	char	*str;
	char	*s;

	while (*node)
	{
		str = (char *)(*node)->content;
		s = skip_spaces(str);
		if (is_map_line(s))
			break ;
		if (handle_header_line(cub, s, floor_set, ceil_set))
			return (-1);
		*node = (*node)->next;
	}
	return (0);
}

/* Valida que el header esté completo. Devuelve 0 ok, -1 error. */
int	validate_header_complete(t_cub *cub,
	int node_exists, int floor_set, int ceil_set)
{
	if (!node_exists)
		return (-1);
	if (!all_textures_set(cub))
		return (-1);
	if (!floor_set || !ceil_set)
		return (-1);
	return (0);
}
