/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 02:35:32 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/25 15:24:40 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_s(char *str, int *res)
{
	size_t	len;

	if (str == NULL)
	{
		write(2, "(null)", 6);
		(*res) = (*res) + 6;
		return ;
	}
	len = ft_strlen(str);
	write(2, str, len);
	(*res) = (*res) + len;
}
