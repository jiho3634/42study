/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:54:46 by jeekpark          #+#    #+#             */
/*   Updated: 2023/04/18 20:50:46 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_del_node(t_node *node)
{
	t_node	*node1;
	t_node	*node2;

	node1 = node->prev_node;
	node2 = node->next_node;
	free(node->content);
	free(node);
	node1->next_node = node2;
	node2->prev_node = node1;
}

static void	ft_del_front_node(t_list *list, t_node *node)
{
	t_node	*node_temp;

	node_temp = node->next_node;
	node_temp->prev_node = NULL;
	free(node->content);
	free(node);
	list->front_node = node_temp;
	list->cur_node = node_temp;
}

static void	ft_del_back_node(t_list *list, t_node *node)
{
	t_node	*node_temp;

	node_temp = node->prev_node;
	node_temp->next_node = NULL;
	free(node->content);
	free(node);
	list->back_node = node_temp;
	list->cur_node = list->front_node;
}

static void	ft_del_cur_node(t_list *list, t_node *node)
{
	ft_del_node(node);
	list->cur_node = list->front_node;
}

int	ft_list_del_node(t_list *list, t_node *node)
{
	if (list == NULL || node == NULL)
		return (ft_error("argument has been wrong", FAILURE));
	if (node->next_node == NULL && node->prev_node == NULL)
	{
		free(node->content);
		free(node);
		*list = ft_list_init();
		return (SUCCESS);
	}
	if (list->front_node == node)
		ft_del_front_node(list, node);
	else if (list->back_node == node)
		ft_del_back_node(list, node);
	else if (list->cur_node == node)
		ft_del_cur_node(list, node);
	else
		ft_del_node(node);
	return (SUCCESS);
}
