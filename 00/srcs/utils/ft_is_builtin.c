/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:26:37 by tnam              #+#    #+#             */
/*   Updated: 2023/06/02 08:42:56 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_exec_info *exec_info)
{
	if (exec_info->cmd_path == NULL)
		return (FALSE);
	if (ft_strncmp(exec_info->cmd[0], "cd", ft_strlen("cd") + 1) == 0
		|| ft_strncmp(exec_info->cmd[0], "export", ft_strlen("export") + 1) == 0
		|| ft_strncmp(exec_info->cmd[0], "unset", ft_strlen("unset") + 1) == 0
		|| ft_strncmp(exec_info->cmd[0], "exit", ft_strlen("exit") + 1) == 0
		|| ft_strncmp(exec_info->cmd[0], "echo", ft_strlen("echo") + 1) == 0
		|| ft_strncmp(exec_info->cmd[0], "pwd", ft_strlen("pwd") + 1) == 0
		|| ft_strncmp(exec_info->cmd[0], "env", ft_strlen("env") + 1) == 0)
		return (TRUE);
	return (FALSE);
}
