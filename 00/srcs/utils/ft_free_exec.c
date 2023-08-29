/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:04:50 by tnam              #+#    #+#             */
/*   Updated: 2023/05/22 22:09:50 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exec(t_exec *exec, size_t exec_arr_i)
{
	size_t		i;

	i = 0;
	while (i < exec_arr_i)
	{
		free(exec->exec_arr[i].cmd);
		free(exec->exec_arr[i].redirect);
		i++;
	}
	free(exec->exec_arr);
	i = 0;
	while (exec->path_envp[i])
		free(exec->path_envp[i++]);
	free(exec->path_envp);
}
