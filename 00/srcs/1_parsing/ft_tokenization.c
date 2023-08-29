/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:28:40 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 14:29:07 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_operator_process(t_parse *parse)
{
	char	redirect_c;

	if (parse->line[parse->line_i] == '|')//pipe일 때,
	{
		if (ft_make_token(parse, PIPE) == FAILURE)//동적할당,복사,구조체에저장
			return (FAILURE);
	}
	else if (ft_is_redirect(parse->line[parse->line_i]) == TRUE)//'<','>' 일 때,
	{
		redirect_c = parse->line[parse->line_i];//문자 복사하고
		if (parse->line[parse->line_i + 1] == redirect_c)//'<<','>>'일 때,
			parse->line_i++;
		if (ft_make_token(parse, REDIRECT) == FAILURE)//동적할당,복사,구조체에저장
			return (FAILURE);
	}
	return (SUCCESS);
}

static void	ft_quote_process(t_parse *parse)
{
	char	end_quote;

	end_quote = parse->line[parse->line_i];
	parse->line_i++;
	while (parse->line[parse->line_i]
		&& parse->line[parse->line_i] != end_quote)
		parse->line_i++;//null이나 quote 문자가 나올 때까지 i++;
}

static int	ft_character_process(t_parse *parse)
{//null, 공백, operator가 아닐 때,
	while (TRUE)
	{
		if (ft_is_quote(parse->line[parse->line_i]) == TRUE)//quote라면
			ft_quote_process(parse);//null이나 quote 문자가 나올 때까지 i++
		if (parse->line[parse->line_i + 1] == '\0'
			|| ft_is_space(parse->line[parse->line_i + 1]) == TRUE
			|| ft_is_operator(parse->line[parse->line_i + 1]) == TRUE)
		{//다음 문자가 null (= 명령어가 끝남) or 공백 or operator 이면
			if (ft_make_token(parse, WORD) == FAILURE)//동적할당,복사,구조체에저장
				return (FAILURE);
			return (SUCCESS);//함수 종료???
		}
		parse->line_i++;
	}
	return (SUCCESS);//null, 공백, operator 가 없으면 token 하지 않고 종료.
}

int	ft_tokenization(t_parse *parse)
{
	while (parse->line[parse->line_i])//null까지 반복
	{
		if (ft_is_space(parse->line[parse->line_i]) == TRUE)//공백
			;
		else if (ft_is_operator(parse->line[parse->line_i]) == TRUE)//operator
		{
			if (ft_operator_process(parse) == FAILURE)
				return (FAILURE);
		}
		else//null or operator가 아니라면 -> 일반문자?
		{
			if (ft_character_process(parse) == FAILURE)
				return (FAILURE);//null, 공백, operator가 나오면 token
		}
		parse->line_i++;
		parse->start_i = parse->line_i;
	}
	return (SUCCESS);
}
