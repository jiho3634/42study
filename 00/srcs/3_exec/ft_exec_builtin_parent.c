/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:31:00 by tnam              #+#    #+#             */
/*   Updated: 2023/06/02 09:37:38 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin_parent(t_info *info, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	exec_info->builtin_parent = TRUE;
	if (ft_strncmp(exec_info->cmd[0], "cd", ft_strlen("cd") + 1) == 0)
		ft_cd_builtin(exec_info);
	if (ft_strncmp(exec_info->cmd[0], "export", ft_strlen("export") + 1) == 0)
		ft_export_builtin(info, exec_info);
	if (ft_strncmp(exec_info->cmd[0], "unset", ft_strlen("unset") + 1) == 0)
		ft_unset_builtin(info, exec_info);
	if (ft_strncmp(exec_info->cmd[0], "exit", ft_strlen("exit") + 1) == 0)
		ft_exit_builtin(&info->mini_envp, parse, exec, exec_info);
	return (SUCCESS);
}
