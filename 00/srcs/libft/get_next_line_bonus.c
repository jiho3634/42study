/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:58:30 by jeekpark          #+#    #+#             */
/*   Updated: 2023/02/10 15:28:52 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_refresh(char *disk)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = ft_gnl_strchr_alt(disk, '\n');
	j = ft_gnl_strlen(disk);
	if (i == j)
	{
		free(disk);
		return (NULL);
	}
	res = (char *) malloc(sizeof(char) * (j - i));
	if (res == NULL)
	{
		free(disk);
		return (NULL);
	}
	i++;
	j = 0;
	while (disk[i])
		res[j++] = disk[i++];
	res[j] = '\0';
	free(disk);
	return (res);
}

static char	*ft_return(char *disk)
{
	char	*res;
	size_t	i;

	if (disk == NULL)
		return (NULL);
	i = ft_gnl_strchr_alt(disk, '\n') + 1;
	if (disk[0] == '\0')
		return (NULL);
	res = ft_gnl_substr(disk, 0, i);
	if (res == NULL)
	{
		free(disk);
		return (NULL);
	}
	return (res);
}

static char	*ft_write_disk(int fd, char *disk)
{
	char	*buf;
	ssize_t	rd_size;

	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		free(disk);
		return (NULL);
	}
	rd_size = 1;
	while (rd_size && ft_gnl_strchr(disk, '\n') == 0)
	{
		rd_size = read(fd, buf, BUFFER_SIZE);
		if (rd_size == -1)
		{
			free(buf);
			free(disk);
			return (NULL);
		}
		buf[rd_size] = '\0';
		disk = ft_gnl_strjoin(disk, buf);
	}
	free(buf);
	return (disk);
}

char	*get_next_line(int fd)
{
	static char	*disk[10240];
	char		*res;

	if (fd < 0 || fd > 10239 || BUFFER_SIZE < 1)
		return (NULL);
	disk[fd] = ft_write_disk(fd, disk[fd]);
	if (disk[fd] == NULL)
		return (NULL);
	res = ft_return(disk[fd]);
	disk[fd] = ft_refresh(disk[fd]);
	return (res);
}
