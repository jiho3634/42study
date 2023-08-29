/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:18:06 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 10:01:22 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_child_exit_code;

void	ft_init(int argc, char **argv, char **envp, t_info *info)
{
	g_child_exit_code = 0;
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
	tcgetattr(STDIN_FILENO, &info->termios_backup);//터미널의 설정을 백업해둠
	ft_mini_envp_init(envp, info);//info -> mini_envp에 환경변수 복사
}
