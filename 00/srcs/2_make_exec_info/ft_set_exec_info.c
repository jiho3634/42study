/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_exec_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:50:30 by tnam              #+#    #+#             */
/*   Updated: 2023/05/22 14:07:46 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_malloc_cmd(t_parse *parse, t_exec_info *exec_info)
{
	size_t	tokens_index;
	size_t	size;

	tokens_index = parse->tokens_i;
	size = 0;
	while (tokens_index < parse->token_count)
	{
		if (parse->tokens[tokens_index].type == PIPE)
			break ;
		if (parse->tokens[tokens_index].type == REDIRECT)
			tokens_index++;
		if (parse->tokens[tokens_index].type == WORD)
			size++;
		tokens_index++;
	}
	exec_info->cmd = (char **)ft_calloc(size + 1, sizeof(char *));
	if (exec_info->cmd == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_malloc_redirect(t_parse *parse, t_exec_info *exec_info)
{
	size_t	tokens_index;
	size_t	size;

	tokens_index = parse->tokens_i;
	size = 0;
	while (tokens_index < parse->token_count)
	{
		if (parse->tokens[tokens_index].type == PIPE)
			break ;
		if (parse->tokens[tokens_index].type == REDIRECT)
			size++;
		tokens_index++;
	}
	exec_info->redirect = (t_redirect *)ft_calloc(size + 1, sizeof(t_redirect));
	if (exec_info->redirect == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static void	ft_add_cmd(t_parse *parse, t_exec_info *exec_info)
{
	exec_info->cmd[exec_info->cmd_i] = parse->tokens[parse->tokens_i].str;
	if (exec_info->cmd_i == 0)
		exec_info->cmd_path = exec_info->cmd[exec_info->cmd_i];
	exec_info->cmd_i++;
}

static void	ft_add_redirect(t_parse *parse, t_exec_info *exec_info)
{
	if (ft_strncmp(parse->tokens[parse->tokens_i].str, ">", 2) == 0)
		exec_info->redirect[exec_info->redirect_i].type = OUT1;
	else if (ft_strncmp(parse->tokens[parse->tokens_i].str, ">>", 3) == 0)
		exec_info->redirect[exec_info->redirect_i].type = OUT2;
	else if (ft_strncmp(parse->tokens[parse->tokens_i].str, "<", 2) == 0)
		exec_info->redirect[exec_info->redirect_i].type = IN1;
	else if (ft_strncmp(parse->tokens[parse->tokens_i].str, "<<", 3) == 0)
		exec_info->redirect[exec_info->redirect_i].type = HERE_DOC;
	exec_info->redirect[exec_info->redirect_i].value
		= parse->tokens[parse->tokens_i + 1].str;
	exec_info->redirect_i++;
}

int	ft_set_exec_info(t_parse *parse, t_exec_info *exec_info)
{
	if (ft_malloc_cmd(parse, exec_info) == FAILURE)
		return (FAILURE);
	if (ft_malloc_redirect(parse, exec_info) == FAILURE)
		return (FAILURE);
	while (parse->tokens_i < parse->token_count)
	{
		if (parse->tokens[parse->tokens_i].type == PIPE)
		{
			exec_info->use_pipe = TRUE;
			parse->tokens_i++;
			break ;
		}
		if (parse->tokens[parse->tokens_i].type == WORD)
			ft_add_cmd(parse, exec_info);
		if (parse->tokens[parse->tokens_i].type == REDIRECT)
		{
			ft_add_redirect(parse, exec_info);
			parse->tokens_i++;
		}
		parse->tokens_i++;
	}
	return (SUCCESS);
}
