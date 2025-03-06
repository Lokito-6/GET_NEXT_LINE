/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:10:43 by lserghin          #+#    #+#             */
/*   Updated: 2024/11/27 23:57:58 by lserghin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_remainder(char *full_line)
{
	char	*variant_line;
	char	*remainder;

	if (!full_line)
		return (NULL);
	variant_line = full_line;
	while (*variant_line && *variant_line != '\n')
		variant_line++;
	if (*variant_line == '\n')
		variant_line++;
	if (*variant_line == '\0')
		return (free(full_line), NULL);
	remainder = ft_strdup(variant_line);
	if (!remainder)
		return (free(full_line), NULL);
	free(full_line);
	return (remainder);
}

static char	*get_line(char *full_line)
{
	char	*variant_line;
	char	*line;

	if (!full_line)
		return (NULL);
	variant_line = full_line;
	while (*variant_line && *variant_line != '\n')
		variant_line++;
	if (*variant_line == '\n')
		variant_line++;
	line = malloc(sizeof(char) * ((variant_line - full_line) + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, full_line, (variant_line - full_line) + 1);
	return (line);
}

static char	*get_full_line(char *full_line, int fd)
{
	char		*buffer;
	ssize_t		bytes_read;
	size_t		buffer_s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_s = BUFFER_SIZE + 1;
	buffer = malloc(sizeof(char) * (buffer_s));
	if (!buffer)
		return (free(full_line), NULL);
	while (ft_strchr(full_line, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(full_line), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		*(buffer + bytes_read) = '\0';
		full_line = ft_strjoin(full_line, buffer);
		if (!full_line)
			return (free(buffer), NULL);
	}
	return (free(buffer), full_line);
}

char	*get_next_line(int fd)
{
	static char	*full_line[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	full_line[fd] = get_full_line(full_line[fd], fd);
	if (!full_line[fd])
		return (NULL);
	line = get_line(full_line[fd]);
	if (!line)
		return (free(full_line[fd]), full_line[fd] = NULL, NULL);
	full_line[fd] = get_remainder(full_line[fd]);
	return (line);
}
