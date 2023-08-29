/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:25:50 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 16:08:28 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parse_init(t_parse *parse)
{
	parse->line_i = 0;
	while (ft_is_space(parse->line[parse->line_i]))
		parse->line_i++;//공백문자들 건너뜀
	parse->token_count = 0;
	parse->tokens_i = 0;
	parse->start_i = 0;
	parse->str_i = 0;
	parse->squote_flag = FALSE;//single quote
	parse->dquote_flag = FALSE;//double quote
}

static int	ft_ready_tokenization(t_parse *parse)
{
	parse->line_i = 0;
	parse->tokens = (t_token *)ft_calloc(parse->token_count, sizeof(t_token));
	if (parse->tokens == NULL)
		return (ft_error("Failed calloc tokens", FAILURE));
	return (SUCCESS);
}

int	ft_parse(t_info *info, t_parse *parse)
{
	ft_parse_init(parse);//parse 구조체 초기화
	if (ft_count_token(parse) == FAILURE)//token 개수 체크
		return (FAILURE);
	if (ft_ready_tokenization(parse) == FAILURE)//token 개수만큼 동적할당
		return (FAILURE);
	if (ft_tokenization(parse) == FAILURE)//공백or operator 기준으로 token
	{
		ft_free_tokens(parse, parse->tokens_i);
		return (FAILURE);
	}
	if (ft_convert_env(info, parse) == FAILURE)
	{
		ft_free_tokens(parse, parse->token_count);
		return (FAILURE);
	}
	ft_remove_quote(parse);
	if (ft_syntax_check(parse) == FAILURE)
	{
		parse->tokens_i = parse->token_count;
		ft_free_tokens(parse, parse->token_count);
		return (FAILURE);
	}
	return (SUCCESS);
}
