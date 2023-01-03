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
	if (node)
	{
		node -> prev = NULL;
		node -> next = NULL;
		node -> remain = NULL;
		node -> fd = fd;
	}
	return (node);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;

	s3 = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (0);
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
	while (s[i])
	{
		if (s[i] == c2)
			return ((char *) &s[i]);
		i++;
	}
	if (!c2)
		return ((char *) &s[i]);
	return (NULL);
}
