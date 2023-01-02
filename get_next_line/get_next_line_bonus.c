/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:25:09 by jihokim2          #+#    #+#             */
/*   Updated: 2022/12/23 14:31:06 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

void	get_ready(int fd, t_list **lst, char **line)
{
	if (!(*lst))
		*lst = ft_lstnew(fd);
	while ((*lst)-> fd != fd)
	{
		if ((*lst)-> next == NULL)
		{
			(*lst)-> next = ft_lstnew(fd);
			((*lst)-> next)-> prev = *lst;
		}
		*lst = (*lst)-> next;
	}
	*line = 0;
	if ((*lst)-> remain != NULL)
	{
		*line = ft_strdup((*lst)-> remain);
		free ((*lst)-> remain);
		(*lst)-> remain = 0;
	}
	return ;
}

int	check_line(t_list **lst, char **line)
{
	char	*temp;

	if (*line)
	{
		temp = ft_strchr(*line, '\n');
		if (temp)
		{
			if (*(++temp))
			{
				(*lst)-> remain = ft_strdup(temp);
				*temp = '\0';
			}
			return (0);
		}
	}
	return (1);
}

void	do_free(t_list **lst, char **line, ssize_t ret)
{
	if ((*lst)-> remain)
	{
		free ((*lst)-> remain);
		(*lst)-> remain = 0;
	}
	if ((*lst)-> prev != NULL)
		((*lst)-> prev)-> next = (*lst)-> next;
	if ((*lst)-> next != NULL)
		((*lst)-> next)-> prev = (*lst)-> prev;
	free (*lst);
	*lst = 0;
	if ((ret != 0) && *line)
	{
		free (*line);
		*line = 0;
	}
	return ;
}

int	make_line(int fd, t_list **lst, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret <= 0)
	{
		do_free(lst, line, ret);
		return (0);
	}
	else
	{
		buf[ret] = '\0';
		temp = ft_strjoin(*line, buf);
		if (*line != 0)
			free (*line);
		*line = temp;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (fd < 0)
		return (NULL);
	get_ready(fd, &lst, &line);
	while (check_line(&lst, &line))
	{
		if (make_line(fd, &lst, &line) == 0)
			break ;
	}
	return (line);
}
