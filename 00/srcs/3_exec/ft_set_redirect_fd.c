/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_redirect_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:26:44 by tnam              #+#    #+#             */
/*   Updated: 2023/05/29 18:22:53 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirect_out1(t_exec_info *exec_info, t_redirect *redirect)
{
	if (exec_info->outfile_fd != NONE)
		if (close(exec_info->outfile_fd) == FAILURE)
			exit(ft_perror(errno));
	exec_info->outfile_fd = open(redirect->value, O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (exec_info->outfile_fd == FAILURE)
		exit(ft_perror(1));
}

static void	ft_redirect_out2(t_exec_info *exec_info, t_redirect *redirect)
{
	if (exec_info->outfile_fd != NONE)
		if (close(exec_info->outfile_fd) == FAILURE)
			exit(ft_perror(errno));
	exec_info->outfile_fd = open(redirect->value, O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if (exec_info->outfile_fd == FAILURE)
		exit(ft_perror(1));
}

static void	ft_redirect_in1(t_exec_info *exec_info, t_redirect *redirect)
{
	if (exec_info->infile_fd != NONE)
		if (close(exec_info->infile_fd) == FAILURE)
			exit(ft_perror(errno));
	exec_info->infile_fd = open(redirect->value, O_RDONLY);
	if (exec_info->infile_fd == FAILURE)
	{
		ft_printf_err("%s: No such file or directory\n", redirect->value);
		exit(1);
	}
}

static void	ft_redirect_here_doc(t_exec_info *exec_info)
{
	if (exec_info->infile_fd != NONE)
		if (close(exec_info->infile_fd) == FAILURE)
			exit(ft_perror(errno));
	exec_info->infile_fd = open("/tmp/whine", O_RDONLY);
	if (exec_info->infile_fd == FAILURE)
		exit(ft_perror(1));
}

void	ft_set_redirect_fd(t_exec_info *exec_info)
{
	t_redirect	*redirect;

	exec_info->redirect_i = 0;
	while (exec_info->redirect[exec_info->redirect_i].value != 0)
	{
		redirect = &exec_info->redirect[exec_info->redirect_i];
		if (redirect->type == OUT1)
			ft_redirect_out1(exec_info, redirect);
		if (redirect->type == OUT2)
			ft_redirect_out2(exec_info, redirect);
		if (redirect->type == IN1)
			ft_redirect_in1(exec_info, redirect);
		if (redirect->type == HERE_DOC)
			ft_redirect_here_doc(exec_info);
		exec_info->redirect_i++;
	}
}
