/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:29:01 by jeekpark          #+#    #+#             */
/*   Updated: 2023/04/18 20:46:27 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	ft_list_init(void)
{
	t_list	res;

	res.front_node = NULL;
	res.back_node = NULL;
	res.cur_node = NULL;
	return (res);
}
