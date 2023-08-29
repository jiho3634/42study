/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:49:54 by jeekpark          #+#    #+#             */
/*   Updated: 2023/06/02 10:29:12 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	else
		return (FALSE);
}

static void	ft_exit_builtin_arg_check(t_exec *exec, size_t i, int sign_flag)
{
	while (exec->exec_arr[exec->exec_arr_i].cmd[1][i])
	{
		if (ft_isnum(exec->exec_arr[exec->exec_arr_i].cmd[1][i]))
			i++;
		else
		{
			ft_printf_err("exit\nexit: %s: numeric argument required\n",
				exec->exec_arr[exec->exec_arr_i].cmd[1]);
			exit(255);
		}
	}
	if (i == 1 && sign_flag == TRUE)
	{
		ft_printf_err("exit\nexit: %s: numeric argument required\n",
			exec->exec_arr[exec->exec_arr_i].cmd[1]);
		exit(255);
	}
}

static void	ft_exit_builtin_isnum(t_exec *exec)
{
	size_t	i;
	int		sign_flag;

	sign_flag = FALSE;
	i = 0;
	if ((exec->exec_arr[exec->exec_arr_i].cmd[1][0] == '-')
		|| (exec->exec_arr[exec->exec_arr_i].cmd[1][0] == '+'))
	{
		sign_flag = TRUE;
		i++;
	}
	ft_exit_builtin_arg_check(exec, i, sign_flag);
}

static void	ft_exit_builtin_no_arg(t_list *mini_envp, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	if ((exec->exec_arr[exec->exec_arr_i].cmd[1]) == NULL)
	{
		ft_list_clear(mini_envp);
		ft_free_all(parse, exec);
		if (exec_info->builtin_parent == TRUE)
			printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

int	ft_exit_builtin(t_list *mini_envp, t_parse *parse, t_exec *exec,
	t_exec_info *exec_info)
{
	int	exit_value;

	ft_exit_builtin_no_arg(mini_envp, parse, exec, exec_info);
	if (exec->exec_arr[exec->exec_arr_i].cmd[2])
	{
		ft_printf_err("exit\nexit: too many arguments\n");
		g_child_exit_code = 1;
		if (exec_info->builtin_parent == TRUE)
			return (SUCCESS);
		else
			exit(1);
	}
	ft_exit_builtin_isnum(exec);
	exit_value = ft_atoi(exec->exec_arr[exec->exec_arr_i].cmd[1]);
	ft_list_clear(mini_envp);
	ft_free_all(parse, exec);
	exit(exit_value);
}
