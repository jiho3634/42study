/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:58:51 by tnam              #+#    #+#             */
/*   Updated: 2023/05/29 18:24:09 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_here_doc(t_redirect *redirect)
{
	char	*input;
	char	*limiter;
	int		temp_fd;

	temp_fd = open("/tmp/whine", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (temp_fd == FAILURE)
		exit(ft_perror(errno));
	limiter = ft_strjoin(redirect->value, "\n");
	if (limiter == NULL)
		exit(ft_error("limiter malloc failed", FAILURE));
	while (TRUE)
	{
		write(1, "> ", 2);
		input = get_next_line(STDIN_FILENO);
		if (!input || ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(temp_fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	free(limiter);
	if (close(temp_fd) == FAILURE)
		exit(ft_perror(errno));
}

static void	ft_search_here_doc(t_exec *exec)
{
	t_exec_info	*exec_info;
	t_redirect	*redirect;

	signal(SIGINT, ft_sig_for_here_doc_child);
	exec->exec_arr_i = 0;
	while (exec->exec_arr_i < exec->exec_arr_size)
	{
		exec_info = &exec->exec_arr[exec->exec_arr_i];
		exec_info->redirect_i = 0;
		while (exec_info->redirect[exec_info->redirect_i].value != 0)
		{
			redirect = &exec_info->redirect[exec_info->redirect_i];
			if (redirect->type == HERE_DOC)
				ft_get_here_doc(redirect);
			exec_info->redirect_i++;
		}
		exec->exec_arr_i++;
	}
	exit(EXIT_SUCCESS);
}

int	ft_check_here_doc(t_exec *exec)
{
	pid_t	here_doc_pid;
	int		child_status;

	here_doc_pid = fork();
	if (here_doc_pid == FAILURE)
		return (FAILURE);
	else if (here_doc_pid == CHILD)
		ft_search_here_doc(exec);
	signal(SIGINT, ft_sig_for_here_doc_parent);
	if (waitpid(-1, &child_status, 0) == FAILURE)
		return (ft_perror(FAILURE));
	g_child_exit_code = WEXITSTATUS(child_status);
	if (g_child_exit_code != EXIT_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
