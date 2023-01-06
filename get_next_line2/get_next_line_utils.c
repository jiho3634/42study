/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:26:33 by jihokim2          #+#    #+#             */
/*   Updated: 2022/12/23 14:32:07 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
{
	t_list	*node;

	node = (t_list *) malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (node)
	{
		node -> prev = NULL;
		node -> next = NULL;
		node -> remain = NULL;
		node -> fd = fd;
	}
	return (node);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	while (s1 && s1[len1])
		len1++;
	len2 = 0;
	while (s2 && s2[len2])
		len2++;
	s3 = (char *) malloc (len1 + len2 + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		s3[i++] = *(s1++);
	while (s2 && *s2)
		s3[i++] = *(s2++);
	s3[i] = 0;
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c2;

	c2 = (char) c;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == c2)
			return ((char *) &s[i]);
		i++;
	}
	if (!c2)
		return ((char *) &s[i]);
	return (NULL);
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

void	all_free(t_list **lst, char **line)
{
	t_list	*temp;

	if (*line)
	{
		free (*line);
		*line = NULL;
	}
	while (*lst)
	{
		if ((*lst)-> remain)
		{
			free ((*lst)-> remain);
			(*lst)-> remain = 0;
		}
		temp = (*lst)-> next;
		free (*lst);
		*lst = temp;
	}
}
