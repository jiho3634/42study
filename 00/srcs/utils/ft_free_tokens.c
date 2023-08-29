/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:04:50 by tnam              #+#    #+#             */
/*   Updated: 2023/05/18 11:42:31 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_parse *parse, size_t token_size)
{
	size_t	i;

	i = 0;
	while (i < token_size)
	{
		free(parse->tokens[i].str);
		i++;
	}
	free(parse->tokens);
}
