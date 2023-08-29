/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:58:01 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/11 15:36:52 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_run(long long n, int fd)
{
	if (n > 9)
		ft_run(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	n_save;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_save = (unsigned int) n * -1;
	}
	else
		n_save = n;
	ft_run(n_save, fd);
}
