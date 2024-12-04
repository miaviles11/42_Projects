/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:00:18 by miaviles          #+#    #+#             */
/*   Updated: 2024/11/13 19:19:15 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_append(int fd, char *remainder)
{
	ssize_t	bytes_read;
	char	*temp;
	char	*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = remainder;
		remainder = ft_strjoin(temp, buffer);
		free(temp);
		if (!remainder)
			return (NULL);
	}
	free(buffer);
	if (bytes_read < 0)
		return (free(remainder), NULL);
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
	char		*line ;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_and_append(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	if (!line)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	remainder = update_remainder(remainder);
	return (line);
}

/*#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("otro.txt", O_RDONLY);
	fd = 42;
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/