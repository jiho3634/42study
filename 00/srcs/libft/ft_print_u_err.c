/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:52:41 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/25 15:24:26 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_run_alt(unsigned int n, int fd, int *res)
{
	if (n > 9)
		ft_run_alt(n / 10, fd, res);
	ft_putchar_fd((n % 10) + '0', fd);
	(*res)++;
}

static void	ft_putnbr_fd_alt(unsigned int n, int fd, int *res)
{
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		(*res)++;
		return ;
	}
	ft_run_alt(n, fd, res);
}

void	ft_print_u(unsigned int nb, int *res)
{
	ft_putnbr_fd_alt(nb, 2, res);
}
