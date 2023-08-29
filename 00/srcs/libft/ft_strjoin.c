/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:33:45 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/17 17:09:28 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (s1 == (void *) 0 || s2 == (void *) 0)
		return ((void *) 0);
	res = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == (void *) 0)
		return ((void *) 0);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		res[i++] = s1[j++];
	}
	j = 0;
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}
