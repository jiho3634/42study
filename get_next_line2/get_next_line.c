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
	*line = 0;
	while (lst -> fd != fd)
	{
		if (lst -> next == NULL)
		{
			lst -> next = ft_lstnew(fd);
			if (lst -> next == NULL)
				return (NULL);
			(lst -> next)-> prev = lst;
		}
		lst = lst -> next;
	}
	if (lst -> remain != NULL)
	{
		*line = lst -> remain;
		lst -> remain = NULL;
	}
	return (lst);
}

int	check_line(t_list **lst, t_list **lst_fd, char **line, char **temp)
{
	*temp = ft_strchr(*line, '\n');
	if (*temp)
	{
		if (*(++(*temp)))
		{
			(*lst_fd)-> remain = ft_strjoin((*lst_fd)-> remain, *temp);
			if ((*lst_fd)-> remain == NULL)
			{
				all_free(lst, line);
				return (0);
			}
			**temp = '\0';
			*temp = ft_strjoin(*line, NULL);
			if (!(*temp))
			{
				all_free(lst, line);
				return (0);
			}
			free (*line);
			*line = *temp;
		}
		return (0);
	}
	return (1);
}

int	add_line(t_list **lst, char **line, char *buf, ssize_t ret)
{
	char	*temp;

	buf[ret] = '\0';
	temp = ft_strjoin(*line, buf);
	free (buf);
	if (!temp)
	{
		all_free(lst, line);
		return (1);
	}
	if (*line)
		free (*line);
	*line = temp;
	return (0);
}

int	make_line(int fd, t_list **lst, t_list **lst_fd, char **line)
{
	char	*buf;
	ssize_t	ret;

	buf = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		all_free (lst, line);
		return (1);
	}
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret <= 0)
	{
		free (buf);
		do_free(lst, lst_fd, line, ret);
		return (1);
	}
	else
		return (add_line(lst, line, buf, ret));
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
	t_list			*lst_fd;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > 2147483646)
		return (NULL);
	if (!lst)
	{
		lst = ft_lstnew(-1);
		if (!lst)
			return (NULL);
	}
	lst_fd = get_ready(fd, lst, &line);
	if (lst_fd == NULL)
	{
		all_free (&lst, &line);
		return (NULL);
	}
	while (check_line(&lst, &lst_fd, &line, &temp))
	{
		if (make_line(fd, &lst, &lst_fd, &line))
			break ;
	}	
	return (line);
}
