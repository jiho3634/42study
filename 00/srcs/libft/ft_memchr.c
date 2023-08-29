/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:54:58 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/10 13:40:14 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_save;
	size_t			i;

	s_save = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (s_save[i] == (unsigned char) c)
			return (&s_save[i]);
		i++;
	}
	return ((void *) 0);
}
