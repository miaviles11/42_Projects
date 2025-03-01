/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:00:18 by miaviles          #+#    #+#             */
/*   Updated: 2024/11/13 18:48:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*remainder[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	remainder[fd] = read_and_fill_buffer(fd, remainder[fd], buffer);
	free(buffer);
	if (!remainder[fd])
		return (NULL);
	line = extract_line(remainder[fd]);
	remainder[fd] = update_remainder(remainder[fd]);
	return (line);
}
/*#include <stdio.h>
int main() {
    int fd1 = open("empty.txt", O_RDONLY);
    int fd2 = open("otro.txt", O_RDONLY); 
    
    if (fd1 < 0 || fd2 < 0) {
        perror("Error opening files");
        return 1;
    }
	int	i = 5;
    while (i > 0) 
	{
		char *line1 = get_next_line(fd1);
    	char *line2 = get_next_line(fd2);
        if (line1) {
            printf("FD1: %s", line1);
            free(line1);
        }
        if (line2) {
            printf("FD2: %s", line2);
            free(line2);
        }
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		i--;
    }

    close(fd1);
    close(fd2);
    return 0;
}*/