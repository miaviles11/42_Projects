/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:15 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:15 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* combine three bytes into 0xRRGGBB -------------------------------------- */
static int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/* PUBLIC: lee línea 'F 220,100,0' o 'C 30,60,90' ------------------------- */
int	parse_color_line(int *dst, char *l)
{
	const char	*s;
	int			r;
	int			g;
	int			b;

	s = skip_spaces(l + 1);
	if (parse_int(&s, &r))
		return (-1);
	if (*s != ',')
		return (-1);
	s++;
	if (parse_int(&s, &g))
		return (-1);
	if (*s != ',')
		return (-1);
	s++;
	if (parse_int(&s, &b))
		return (-1);
	s = skip_spaces((char *)s);
	if (*s != '\0')
		return (-1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	*dst = rgb_to_int(r, g, b);
	return (0);
}
