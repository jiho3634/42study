/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:44:46 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/11 15:36:04 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_case_zero(void)
{
	char	*res;

	res = (char *) malloc(sizeof(char) * 2);
	if (res == (void *) 0)
		return ((void *) 0);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static void	ft_is_negative(int n, int *sign, unsigned int *tmp, size_t *i)
{
	*sign = 1;
	*i = 0;
	if (n < 0)
	{
		*sign = -1;
		*tmp = n * -1;
		*i = *i + 1;
	}
	else
		*tmp = n;
}

static size_t	ft_count_len(unsigned int tmp, int sign)
{
	size_t	i;

	i = 0;
	while (tmp != 0)
	{
		tmp = tmp / 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int				sign;
	size_t			i;
	unsigned int	tmp;
	char			*res;

	ft_is_negative(n, &sign, &tmp, &i);
	if (n == 0)
		return (ft_case_zero());
	i = ft_count_len(tmp, sign);
	res = (char *) malloc(sizeof(char) * (i + 1));
	if (res == (void *) 0)
		return ((void *) 0);
	res[i] = '\0';
	i--;
	while (i != 0)
	{
		res[i] = (tmp % 10) + '0';
		tmp = tmp / 10;
		i--;
	}
	res[i] = (tmp % 10) + '0';
	if (sign == -1)
		res[0] = '-';
	return (res);
}
