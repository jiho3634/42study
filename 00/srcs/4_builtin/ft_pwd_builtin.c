/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:44:04 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/24 19:55:32 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd_builtin(void)
{
	char	path[256];

	if (getcwd(path, sizeof(path)))
		printf("%s\n", path);
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
