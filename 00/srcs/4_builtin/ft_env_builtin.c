/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:19:03 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/29 11:38:19 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_builtin_has_value(char *content)
{
	size_t	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_env_builtin(t_info *info)
{
	t_node	*cur;

	cur = info->mini_envp.front_node;
	while (cur)
	{
		if (ft_env_builtin_has_value(cur->content) == TRUE)
			printf("%s\n", (char *)(cur->content));
		cur = cur->next_node;
	}
	exit(EXIT_SUCCESS);
}
