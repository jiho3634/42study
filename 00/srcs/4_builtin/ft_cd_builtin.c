/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:39:21 by tnam              #+#    #+#             */
/*   Updated: 2023/06/06 10:42:24 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_builtin(t_exec_info *exec_info)
{
	char	*path;

	path = exec_info->cmd[1];
	if (path == NULL)
	{
		if (exec_info->builtin_parent == TRUE)
			return (SUCCESS);
		else
			exit(EXIT_SUCCESS);
	}
	if (chdir(path) == FAILURE)
	{
		g_child_exit_code = 1;
		if (exec_info->builtin_parent == TRUE)
		{
			ft_printf_err("cd: %s: ", path);
			return (ft_perror(SUCCESS));
		}
		else
			exit(EXIT_SUCCESS);
	}
	if (exec_info->builtin_parent == TRUE)
		return (SUCCESS);
	else
		exit(EXIT_SUCCESS);
}
