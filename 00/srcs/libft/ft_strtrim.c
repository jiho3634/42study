/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:42:17 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/17 15:52:54 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;
	size_t	i;
	char	*res;

	s = 0;
	e = (size_t) ft_strlen(s1);
	while (s1[s] && ft_strchr(set, s1[s]) != 0)
		s++;
	while (e > 0 && ft_strchr(set, s1[e]) != 0)
		e--;
	if (s > e || (s == 0 && e == 0))
		i = 1;
	else
		i = e - s + 2;
	res = (char *) malloc(sizeof(char) * i);
	if (res == (void *) 0)
		return ((void *) 0);
	i = 0;
	while (s <= e && s + e != 0)
		res[i++] = s1[s++];
	res[i] = '\0';
	return (res);
}
