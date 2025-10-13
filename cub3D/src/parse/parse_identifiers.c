/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:19 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:19 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* ----------------------- helpers locales de espacios --------------------- */
static int	is_space(int c)
{
	return (c == ' ' || c == '\t');
}

static char	*ltrim(const char *s)
{
	while (*s && is_space((unsigned char)*s))
		s++;
	return ((char *)s);
}

static size_t	rtrim_len(const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	while (len && (s[len - 1] == ' ' || s[len - 1] == '\t'
			|| s[len - 1] == '\n' || s[len - 1] == '\r'))
		len--;
	return (len);
}

/* guarda la ruta eliminando \n, \r, espacios y tabs finales ---------------- */
static int	store_texture(t_cub *cub, int idx, const char *after_id)
{
	char	*clean;
	size_t	len;

	if (cub->textures[idx].path)
		return (-1);
	clean = ltrim(after_id);
	len = rtrim_len(clean);
	if (len == 0)
		return (-1);
	cub->textures[idx].path = ft_substr(clean, 0, len);
	if (!cub->textures[idx].path)
		return (-1);
	return (0);
}

/* ---------------- PUBLIC: texture identifiers (NO / SO / WE / EA) -------- */
int	parse_texture_line(t_cub *cub, char *l)
{
	char	*s;

	if (!l || !cub)
		return (-1);
	s = ltrim(l);
	if (!ft_strncmp(s, "NO", 2) && is_space((unsigned char)s[2]))
		return (store_texture(cub, DIR_NORTH, s + 2));
	if (!ft_strncmp(s, "SO", 2) && is_space((unsigned char)s[2]))
		return (store_texture(cub, DIR_SOUTH, s + 2));
	if (!ft_strncmp(s, "WE", 2) && is_space((unsigned char)s[2]))
		return (store_texture(cub, DIR_WEST, s + 2));
	if (!ft_strncmp(s, "EA", 2) && is_space((unsigned char)s[2]))
		return (store_texture(cub, DIR_EAST, s + 2));
	return (-1);
}
