/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:43:09 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 12:49:48 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_make_token(t_parse *parse, t_token_type type)//type = pipe
{
	parse->tokens[parse->tokens_i].type = type;
	parse->temp_str
		= (char *)ft_calloc(parse->line_i - parse->start_i + 2, sizeof(char));
	if (parse->temp_str == NULL)
		return (ft_error("Failed malloc temp_str", FAILURE));
	ft_strlcpy(parse->temp_str, &parse->line[parse->start_i],
		parse->line_i - parse->start_i + 2);
	parse->tokens[parse->tokens_i].str = parse->temp_str;
	parse->tokens_i++;
	return (SUCCESS);
}
