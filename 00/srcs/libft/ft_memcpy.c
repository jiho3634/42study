/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:56:14 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/10 12:01:37 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_save;
	unsigned char	*src_save;

	i = 0;
	dst_save = (unsigned char *) dst;
	src_save = (unsigned char *) src;
	if (dst_save == (void *) 0 && src_save == (void *) 0)
		return (dst);
	while (i < n)
	{
		dst_save[i] = src_save[i];
		i++;
	}
	return (dst_save);
}
