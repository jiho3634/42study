/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:02:57 by tnam              #+#    #+#             */
/*   Updated: 2023/05/29 18:24:01 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_pipe_syntax(t_parse *parse)
{
	if (parse->tokens_i == 0 || parse->tokens_i == parse->token_count - 1)
	{
		g_child_exit_code = 258;
		return (ft_error("Syntax Error: PIPE became first or last", FAILURE));
	}
	else
	{
		if (parse->tokens[parse->tokens_i - 1].type == PIPE
			|| parse->tokens[parse->tokens_i + 1].type == PIPE)
		{
			g_child_exit_code = 258;
			return (ft_error("Syntax Error: No word between PIPE", FAILURE));
		}
	}
	return (SUCCESS);
}

static int	ft_check_redirect_syntax(t_parse *parse)
{
	if (parse->tokens_i == parse->token_count - 1)
	{
		g_child_exit_code = 258;
		return (ft_error("Syntax Error: No word after REDIRECT", FAILURE));
	}
	else
	{
		if (parse->tokens[parse->tokens_i + 1].type != WORD)
		{
			g_child_exit_code = 258;
			return (ft_error("Syntax Error: No word after REDIRECT", FAILURE));
		}
	}
	return (SUCCESS);
}

int	ft_syntax_check(t_parse *parse)
{
	parse->tokens_i = 0;
	while (parse->tokens_i < parse->token_count)
	{
		if (parse->tokens[parse->tokens_i].type == PIPE)
		{
			if (ft_check_pipe_syntax(parse) == FAILURE)
				return (FAILURE);
		}
		else if (parse->tokens[parse->tokens_i].type == REDIRECT)
		{
			if (ft_check_redirect_syntax(parse) == FAILURE)
				return (FAILURE);
		}
		parse->tokens_i++;
	}
	return (SUCCESS);
}
