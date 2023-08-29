/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:59:17 by tnam              #+#    #+#             */
/*   Updated: 2023/05/22 22:10:04 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_parse *parse, t_exec *exec)
{
	ft_free_tokens(parse, parse->token_count);
	ft_free_exec(exec, exec->exec_arr_size);
}
