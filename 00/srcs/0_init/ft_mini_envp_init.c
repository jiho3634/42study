/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_envp_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:15:44 by jeekpark          #+#    #+#             */
/*   Updated: 2023/08/28 19:17:43 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mini_envp_init(char **envp, t_info *info)
{
	size_t	i;

	i = 0;
	info->mini_envp = ft_list_init();
	while (envp[i])
	{
		ft_list_push_back(ft_strdup(envp[i]), &(info->mini_envp));
		i++;
	}
}
