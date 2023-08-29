/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:03:02 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/10 13:37:14 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	i;

	if (s == (void *) 0 || f == (void *) 0)
		return ((void *) 0);
	res = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == (void *) 0)
		return ((void *) 0);
	i = 0;
	while (i < (size_t) ft_strlen(s))
	{
		res[i] = f((unsigned int) i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
