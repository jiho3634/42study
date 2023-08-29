/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:13:22 by tnam              #+#    #+#             */
/*   Updated: 2023/05/24 14:20:35 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_pipe_fd(t_exec *exec, t_exec_info *exec_info)
{
	if (exec->prev_pipe_fd != NONE)
	{
		if (dup2(exec->prev_pipe_fd, STDIN_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(exec->prev_pipe_fd) == FAILURE)
			exit(ft_perror(errno));
	}
	if (exec_info->use_pipe == TRUE)
	{
		if (dup2(exec_info->pipe_fd[OUT], STDOUT_FILENO) == FAILURE)
			exit(ft_perror(errno));
		if (close(exec_info->pipe_fd[OUT]) == FAILURE)
			exit(ft_perror(errno));
		if (close(exec_info->pipe_fd[IN]) == FAILURE)
			exit(ft_perror(errno));
	}
}
