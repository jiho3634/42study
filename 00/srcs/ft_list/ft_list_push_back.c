/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:22:55 by jeekpark          #+#    #+#             */
/*   Updated: 2023/04/18 20:46:37 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_push_back(void *content, t_list *list)
{
	t_node	*node;

	if (list == NULL || content == NULL)
		return (ft_error("argument has been wrong", FAILURE));
	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (ft_error("malloc returns NULL", FAILURE));
	node->content = content;
	node->next_node = NULL;
	node->prev_node = list->back_node;
	if (node->prev_node != NULL)
		node->prev_node->next_node = node;
	if (list->front_node == NULL)
	{
		list->front_node = node;
		list->back_node = node;
		list->cur_node = node;
		return (SUCCESS);
	}
	list->back_node = node;
	return (SUCCESS);
}
