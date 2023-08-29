/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:34:56 by tnam              #+#    #+#             */
/*   Updated: 2023/05/25 18:11:28 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_make_path_envp(t_info *info, t_parse *parse, t_exec *exec)
{
	char	*path;
	t_node	*node;

	node = info->mini_envp.front_node;
	while (node && ft_strncmp(node->content, "PATH=", 5) != 0)
		node = node->next_node;
	if (node == NULL)
	{
		exec->path_envp = (char **)ft_calloc(1, sizeof(char *));
		if (exec->path_envp == NULL)
			return (ft_error("exec->path_envp malloc failed.", FAILURE));
		return (SUCCESS);
	}
	path = node->content + 5;
	exec->path_envp = ft_split(path, ':');
	if (exec->path_envp == NULL)
	{
		ft_free_tokens(parse, parse->token_count);
		return (ft_error("exec->path_envp split failed.", FAILURE));
	}
	return (SUCCESS);
}

int	ft_init_exec(t_info *info, t_parse *parse, t_exec *exec)
{
	if (ft_make_path_envp(info, parse, exec) == FAILURE)
		return (FAILURE);
	exec->exec_arr_i = 0;
	exec->prev_pipe_fd = NONE;
	exec->exec_arr
		= (t_exec_info *)malloc(sizeof(t_exec_info) * exec->exec_arr_size);
	if (exec->exec_arr == NULL)
	{
		free(exec->path_envp);
		ft_free_tokens(parse, parse->token_count);
		return (ft_error("exec_arr malloc failed.", FAILURE));
	}
	return (SUCCESS);
}
