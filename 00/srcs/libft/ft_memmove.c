/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:56:24 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/14 09:42:05 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dst_save;
	const unsigned char	*src_save = (const unsigned char *) src;

	dst_save = (unsigned char *) dst;
	if (dst_save == (void *) 0 && src_save == (void *) 0)
		return ((void *) 0);
	if (dst_save < src_save)
	{
		i = -1;
		while (++i < len)
			dst_save[i] = src_save[i];
	}
	else if (dst_save >= src_save)
	{
		i = len;
		while (i > 0)
		{
			dst_save[i - 1] = src_save[i - 1];
			i--;
		}
	}
	return (dst);
}
