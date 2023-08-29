/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 00:03:35 by jeekpark          #+#    #+#             */
/*   Updated: 2023/02/10 15:28:23 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_gnl_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

size_t	ft_gnl_strchr_alt(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (i);
		i++;
	}
	if ((unsigned char) c == '\0')
		return (i);
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_gnl_strlen(s1);
	s2_len = ft_gnl_strlen(s2);
	res = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (res == NULL)
		free(s1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
		res[i++] = s1[j++];
	j = 0;
	while (i < s1_len + s2_len)
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;

	s_len = ft_gnl_strlen(s);
	if (len > s_len - (size_t) start)
		i = s_len - (size_t) start + 1;
	else
		i = len + 1;
	if (s_len < (size_t) start || s_len == 0)
		i = 1;
	res = (char *) malloc(sizeof(char) * i);
	if (res == (void *) 0)
		return ((void *) 0);
	i = 0;
	while ((size_t) start + i < s_len && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
