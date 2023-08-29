/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:30:49 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/09 17:02:39 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	save;

	i = 0;
	j = 0;
	save = ft_strlen(dst);
	if ((size_t) ft_strlen(dst) >= dstsize)
		return (ft_strlen(src) + dstsize);
	else
	{
		while (dst[i])
			i++;
		while (src[j] && (dstsize - save) - 1 > 0)
		{
			dst[i + j] = src[j];
			j++;
			dstsize--;
		}
		dst[i + j] = '\0';
		return (save + ft_strlen(src));
	}
}
