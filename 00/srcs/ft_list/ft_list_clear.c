/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:41:01 by jeekpark          #+#    #+#             */
/*   Updated: 2023/04/18 20:50:45 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_clear(t_list *list)
{
	list->cur_node = list->front_node;
	while (list->cur_node)
		ft_list_del_node(list, list->cur_node);
}
