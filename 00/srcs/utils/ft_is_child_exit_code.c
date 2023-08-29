/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_child_exit_code.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:16:42 by tnam              #+#    #+#             */
/*   Updated: 2023/05/23 17:46:48 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_child_exit_code(t_parse *parse)
{
	if (parse->token->str[parse->str_i + 1] == '?')
		return (TRUE);
	return (FALSE);
}
