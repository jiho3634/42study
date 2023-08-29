/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:22:10 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/25 15:24:15 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_ibase_num(unsigned int nbr, char *base, int *res)
{
	if (nbr == 0)
		return ;
	print_ibase_num(nbr / 16, base, res);
	write(2, &base[nbr % 16], 1);
	(*res)++;
}

void	ft_print_x(unsigned int nbr, char x, int *res)
{
	char			*base;

	if (x == 'x')
		base = "0123456789abcdef";
	else if (x == 'X')
		base = "0123456789ABCDEF";
	if (nbr == 0)
	{
		write(2, &base[0], 1);
		(*res)++;
		return ;
	}
	print_ibase_num(nbr, base, res);
}
