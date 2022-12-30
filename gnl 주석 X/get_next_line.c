/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:25:09 by jihokim2          #+#    #+#             */
/*   Updated: 2022/12/23 14:31:06 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

static int	exception(int fd, t_list **lst)
{
	if (fd < 0)
	{
		if (*lst)
		{
			free (*lst);
			*lst = 0;
		}
		return (-1);
	}
	return (0);
}

static t_list	*set_lst(t_list *lst, int fd)
{
	t_list	*new;

	if (!lst)
		lst = ft_lstnew(fd);
	while (lst -> fd != fd)
	{
		if (lst -> next == NULL)
		{
			new = ft_lstnew(fd);
			ft_lstadd_back(&lst, new);
		}
		lst = lst -> next;
	}
	return (lst);
}

static void	check_remain(t_list **lst, char **line)
{
	if ((*lst)-> remain != NULL)
	{
		*line = ft_strdup((*lst)-> remain);
		free ((*lst)-> remain);
		(*lst)-> remain = 0;
	}
}

static int	check_line(t_list **lst, char **line)
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

static int	get_line(int fd, t_list **lst, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret < 0)
	{
		if ((*lst))
		{
			if ((*lst)-> remain)
			{
				free ((*lst)-> remain);
				(*lst)-> remain = 0;
			}
			if ((*lst)-> prev != NULL)
				((*lst)-> prev) -> next = (*lst)-> next;
			if ((*lst)-> next != NULL)
				((*lst)-> next) -> prev = (*lst)-> prev;
			free (*lst);
			*lst = 0;
			if (*line)
			{
				free (*line);
				*line = 0;
			}
		}
		return (0);
	}
	else if (ret == 0)
	{
		if ((*lst)-> remain == NULL)
		{
			if ((*lst)-> prev != NULL)
				((*lst)-> prev) -> next = (*lst)-> next;
			if ((*lst)-> next != NULL)
				((*lst)-> next) -> prev = (*lst)-> prev;
			free (*lst);
			*lst = 0;
		}
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

	if (exception(fd, &lst))
		return (NULL);
	lst = set_lst(lst, fd);
	line = 0;
	check_remain(&lst, &line);
	while (check_line(&lst, &line) != 0)
	{
		if (get_line(fd, &lst, &line) == 0)
			break;
	}
	return (line);
}
