/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:21:41 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/17 17:11:31 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			i;

	if (len > ft_strlen(s) - (size_t) start)
		i = ft_strlen(s) - (size_t) start + 1;
	else
		i = len + 1;
	if (ft_strlen(s) < (size_t) start || ft_strlen(s) == 0)
		i = 1;
	res = (char *) malloc(sizeof(char) * i);
	if (res == (void *) 0)
		return ((void *) 0);
	i = 0;
	while ((size_t) start + i < ft_strlen(s) && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
