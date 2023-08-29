/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:56:27 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/10 13:47:55 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = ft_strlen(s1);
	j = 0;
	res = (char *) malloc(sizeof(char) * i + 1);
	if (res == (void *) 0)
		return ((void *) 0);
	while (s1[j])
	{
		res[j] = s1[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}
