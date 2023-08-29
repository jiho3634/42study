/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:26:41 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/11 12:47:32 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_save;
	unsigned char	*s2_save;
	size_t			i;

	s1_save = (unsigned char *) s1;
	s2_save = (unsigned char *) s2;
	i = 0;
	while (i < n && s1_save[i] == s2_save[i])
		i++;
	if (i < n)
		return ((int) s1_save[i] - (int) s2_save[i]);
	return (0);
}
