/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:51:08 by tnam              #+#    #+#             */
/*   Updated: 2023/04/28 20:05:30 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_env(t_info *info, t_parse *parse)
{
	t_node	*env_node;

	env_node = info->mini_envp.front_node;
	while (env_node)
	{
		if (ft_strncmp(env_node->content, parse->target_env,
				ft_strlen(parse->target_env)) == 0)
		{
			parse->env_val = ft_strdup(ft_strchr(env_node->content, '=') + 1);
			parse->env_val_len = ft_strlen(parse->env_val);
			return (TRUE);
		}
		if (env_node->next_node == NULL)
			break ;
		env_node = env_node->next_node;
	}
	return (FALSE);
}
