/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:49:08 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/10 20:41:34 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle == haystack || needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[i] && i + (size_t)ft_strlen(needle) <= len)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] && haystack[i + j] == needle[j])
			{
				j++;
				if (i + j > len)
					return ((void *) 0);
				if (needle[j] == '\0')
					return ((char *) &haystack[i]);
			}
			j = 0;
		}
		i++;
	}
	return ((void *) 0);
}
