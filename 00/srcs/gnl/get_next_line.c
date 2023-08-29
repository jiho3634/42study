/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:22:31 by tnam              #+#    #+#             */
/*   Updated: 2023/03/02 14:28:30 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read(int fd, char **contents, char **buffer)
{
	ssize_t	read_size;

	*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buffer == NULL)
		return (-1);
	read_size = read(fd, *buffer, BUFFER_SIZE);
	if (read_size < 0)
	{
		free(*buffer);
		if (*contents)
		{
			free(*contents);
			*contents = NULL;
		}
		return (-1);
	}
	return (read_size);
}

char	*ft_make_contents(char *contents, char *buffer)
{
	if (contents == NULL)
	{
		contents = malloc(1);
		if (contents == NULL)
		{
			contents = NULL;
			return (NULL);
		}
		*contents = '\0';
	}
	contents = ft_strjoin_gnl(contents, buffer);
	if (contents == NULL)
	{
		free(buffer);
		return (NULL);
	}
	return (contents);
}

char	*ft_split_contents_to_line(char **contents)
{
	size_t	line_len;
	size_t	contents_len;
	size_t	new_contents_len;
	char	*line;
	char	*new_contents;

	line_len = 0;
	while (contents[0][line_len] != '\n')
		line_len++;
	contents_len = ft_strlen(*contents);
	new_contents_len = contents_len - line_len + 1;
	line = malloc(sizeof(char) * (line_len + 2));
	if (line == NULL)
		return (NULL);
	new_contents = malloc(sizeof(char) * (new_contents_len + 1));
	if (new_contents == NULL)
	{
		free(line);
		return (NULL);
	}
	ft_make_line(line, *contents, line_len);
	new_contents = ft_new_contents(new_contents, *contents, line_len + 1);
	free(*contents);
	*contents = new_contents;
	return (line);
}

char	*ft_eof(char **contents)
{
	char	*temp;

	if (**contents == '\0')
	{
		free(*contents);
		*contents = NULL;
		return (NULL);
	}
	temp = *contents;
	*contents = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*contents;
	char		*line;
	char		*buffer;
	ssize_t		read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		read_size = ft_read(fd, &contents, &buffer);
		if (read_size < 0)
			return (NULL);
		buffer[read_size] = '\0';
		contents = ft_make_contents(contents, buffer);
		if (contents == NULL)
			return (NULL);
		if (ft_strchr(contents, '\n'))
		{
			line = ft_split_contents_to_line(&contents);
			return (line);
		}
		if (read_size < BUFFER_SIZE)
			return (ft_eof(&contents));
	}
}
