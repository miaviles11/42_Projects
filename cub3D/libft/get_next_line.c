/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:00:18 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/20 18:16:46 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_and_append(int fd, char *remainder, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(remainder);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = remainder;
		remainder = ft_strjoin(temp, buffer);
		free(temp);
		if (!remainder)
			return (NULL);
	}
	return (remainder);
}

static char	*read_and_fill_buffer(int fd, char *remainder, char *buffer)
{
	if (!remainder)
	{
		remainder = (char *)malloc(1);
		remainder[0] = '\0';
		if (!remainder)
			return (NULL);
	}
	remainder = read_and_append(fd, remainder, buffer);
	return (remainder);
}

static char	*extract_line(char *remainder)
{
	char	*line;
	char	*newline_pos;
	size_t	len;

	if (!remainder || *remainder == '\0')
		return (NULL);
	newline_pos = ft_strchr(remainder, '\n');
	if (newline_pos)
	{
		len = (size_t)(newline_pos - remainder) + 1;
		line = ft_substr(remainder, 0, len);
	}
	else
	{
		len = ft_strlen(remainder) + 1;
		line = ft_substr(remainder, 0, len);
	}
	if (!line)
		return (NULL);
	return (line);
}

static char	*update_remainder(char *remainder)
{
	char	*tmp;
	char	*updated_remainder;

	if (!remainder)
		return (NULL);
	tmp = ft_strchr(remainder, '\n');
	if (tmp)
	{
		updated_remainder = ft_strdup(tmp + 1);
		if (!updated_remainder)
		{
			free(remainder);
			return (NULL);
		}
	}
	else
		updated_remainder = NULL;
	free(remainder);
	return (updated_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line ;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	remainder = read_and_fill_buffer(fd, remainder, buffer);
	free(buffer);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}
