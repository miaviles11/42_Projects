/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:06:04 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 16:06:04 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* skip until first map line ------------------------------------------------ */
int	skip_to_map(int fd, char **line)
{
	*line = get_next_line(fd);
	while (*line && !is_map_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}

/* drena GNL hasta EOF para liberar la stash del fd ------------------------- */
void	gnl_drain(int fd)
{
	char	*s;

	s = get_next_line(fd);
	while (s != NULL)
	{
		free(s);
		s = get_next_line(fd);
	}
}

/* true si la línea es solo espacios/tabs/CR/LF ----------------------------- */
int	is_blank_line(const char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
		s++;
	return (*s == '\0');
}
