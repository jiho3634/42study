/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:01:06 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/25 15:24:04 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printf_pointer(void *arg, char type, int *res)
{
	if (type == 's')
		ft_print_s((char *)arg, res);
	else if (type == 'p')
		ft_print_p(arg, res);
}

static void	ft_printf_unsinged_int(unsigned int arg, char type, int *res)
{
	if (type == 'x' || type == 'X')
		ft_print_x(arg, type, res);
	else if (type == 'u')
		ft_print_u(arg, res);
}

static void	ft_printf_int(int arg, char type, int *res)
{
	if (type == 'c')
		ft_print_c(arg, res);
	else if (type == 'd' || type == 'i')
		ft_print_di(arg, res);
}

static int	ft_print(va_list arg, const char *format, int res)
{
	int	i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c' || format[i] == 'd' || format[i] == 'i')
				ft_printf_int(va_arg(arg, int), format[i], &res);
			else if (format[i] == 'x' || format[i] == 'X' || format[i] == 'u')
				ft_printf_unsinged_int(va_arg(arg, unsigned), format[i], &res);
			else if (format[i] == 's' || format[i] == 'p')
				ft_printf_pointer(va_arg(arg, void *), format[i], &res);
			else if (format[i] == '%')
				ft_print_c('%', &res);
			else
				return (-1);
		}
		else
			ft_print_c(format[i], &res);
	}
	return (res);
}

int	ft_printf_err(const char *format, ...)
{
	va_list	arg;
	int		res;

	va_start(arg, format);
	res = ft_print(arg, format, 0);
	va_end(arg);
	return (res);
}
