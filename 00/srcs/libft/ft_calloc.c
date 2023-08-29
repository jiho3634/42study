/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:03:47 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/11 15:45:04 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;

	res = (char *) malloc(count * size);
	if (res == (void *) 0)
		return ((void *) 0);
	ft_bzero(res, count * size);
	return ((void *) res);
}
