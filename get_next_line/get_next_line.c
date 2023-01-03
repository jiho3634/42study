/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:25:09 by jihokim2          #+#    #+#             */
/*   Updated: 2022/12/23 14:31:06 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_ready(int fd, t_list *lst, char **line)
{
	while ((lst)-> fd != fd)
	{
		if ((lst)-> next == NULL)
		{
			(lst)-> next = ft_lstnew(fd);
			((lst)-> next)-> prev = lst;
		}
		lst = (lst)-> next;
	}
	*line = 0;
	if ((lst)-> remain != NULL)
	{
		*line = (lst)-> remain;
		(lst)-> remain = NULL;
	}
	return (lst);
}

int	check_line(t_list *lst_fd, char **line)
{
	char	*temp;

	if (*line)
	{
		temp = ft_strchr(*line, '\n');
		if (temp)
		{
			if (*(++temp))
			{
				(lst_fd)-> remain = ft_strjoin((lst_fd)-> remain, temp);
				*temp = '\0';
			}
			return (0);
		}
	}
	return (1);
}

void	do_free(t_list **lst, t_list **lst_fd, char **line, ssize_t ret)
{
	if ((*lst_fd)-> prev)
		((*lst_fd)-> prev)-> next = (*lst_fd)-> next;
	if ((*lst_fd)-> next)
		((*lst_fd)-> next)-> prev = (*lst_fd)-> prev;
	free (*lst_fd);
	if ((*lst)-> next == NULL)
	{
		free (*lst);
		*lst = 0;
	}
	if (ret && *line)
	{
		free (*line);
		*line = 0;
	}
}

int	make_line(int fd, t_list **lst, t_list **lst_fd, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret <= 0)
	{
		do_free(lst, lst_fd, line, ret);
		return (1);
	}
	else
	{
		buf[ret] = '\0';
		temp = ft_strjoin(*line, buf);
		if (*line)
			free (*line);
		*line = temp;
		return (0);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
	t_list			*lst_fd;

	if (fd < 0)
		return (NULL);
	if (!lst)
		lst = ft_lstnew(-1);
	lst_fd = get_ready(fd, lst, &line);
	while (check_line(lst_fd, &line))
	{
		if (make_line(fd, &lst, &lst_fd, &line))
			break ;
	}
	return (line);
}
