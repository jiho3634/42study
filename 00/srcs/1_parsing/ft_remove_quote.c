/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:51:59 by tnam              #+#    #+#             */
/*   Updated: 2023/05/02 14:19:47 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_find_quote(t_parse *parse)
{
	char	c;
	char	quote;

	c = parse->token->str[parse->str_i];
	if (ft_is_quote(c) == TRUE)
	{
		quote = c;
		parse->start_i = parse->str_i;
		parse->str_i++;
		while (parse->token->str[parse->str_i] != quote)
			parse->str_i++;
		ft_strlcpy(&parse->token->str[parse->start_i],
			&parse->token->str[parse->start_i] + 1,
			ft_strlen(&parse->token->str[parse->start_i]));
		ft_strlcpy(&parse->token->str[parse->str_i - 1],
			&parse->token->str[parse->str_i],
			ft_strlen(&parse->token->str[parse->str_i - 1]));
		parse->str_i -= 2;
	}
}

void	ft_remove_quote(t_parse *parse)
{
	parse->tokens_i = 0;
	while (parse->tokens_i < parse->token_count)
	{
		parse->token = &parse->tokens[parse->tokens_i];
		parse->str_i = 0;
		while (parse->token->str[parse->str_i])
		{
			ft_find_quote(parse);
			parse->str_i++;
		}
		parse->tokens_i++;
	}
}
