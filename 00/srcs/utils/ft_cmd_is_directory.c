/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:35:23 by tnam              #+#    #+#             */
/*   Updated: 2023/05/29 17:56:45 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_is_directory(char *cmd_path)
{
	DIR	*dir;

	dir = opendir(cmd_path);
	if (dir != NULL)
	{
		ft_printf_err("%s: is a directory\n", cmd_path);
		exit(126);
	}
}
