/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:25:24 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/25 15:25:18 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_ibase_num(size_t nbr, char *base, int *res)
{
	if (nbr == 0)
		return ;
	print_ibase_num(nbr / 16, base, res);
	write(2, &base[nbr % 16], 1);
	(*res)++;
}

void	ft_print_p(void *addr, int *res)
{
	size_t	nbr;
	char	*base;

	base = "0123456789abcdef";
	nbr = (size_t)addr;
	write(2, "0x", 2);
	(*res) = (*res) + 2;
	if (nbr == 0)
	{
		write(2, &base[0], 1);
		(*res)++;
		return ;
	}
	print_ibase_num(nbr, base, res);
}
