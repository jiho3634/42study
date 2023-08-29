/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:39:21 by tnam              #+#    #+#             */
/*   Updated: 2023/06/02 08:58:20 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_echo_builtin_malloc_str(t_exec_info *exec_info)
{
	char	**str;
	size_t	str_size;

	str_size = 1;
	while (exec_info->cmd[str_size])
		str_size++;
	str = (char **)ft_calloc(str_size, sizeof(char *));
	if (str == NULL)
		exit(EXIT_FAILURE);
	return (str);
}

static int	ft_echo_builtin_is_n(char *str)
{
	size_t	i;

	if (ft_strncmp(str, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static size_t	ft_echo_builtin_find_cmd_i(char **cmd, int *n_flag)
{
	size_t	cmd_i;

	cmd_i = 1;
	while (cmd[cmd_i])
	{
		if (ft_echo_builtin_is_n(cmd[cmd_i]) == FALSE)
			return (cmd_i);
		*n_flag = TRUE;
		cmd_i++;
	}
	exit(EXIT_SUCCESS);
}

static void	ft_echo_builtin_print_str(char **str, int n_flag)
{
	size_t	i;

	i = 0;
	while (str[i + 1])
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("%s", str[i]);
	if (n_flag == FALSE)
		printf("\n");
}

int	ft_echo_builtin(t_exec_info *exec_info)
{
	char	**str;
	size_t	str_i;
	size_t	cmd_i;
	int		n_flag;

	if (exec_info->cmd[1] == NULL)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	str = ft_echo_builtin_malloc_str(exec_info);
	n_flag = FALSE;
	str_i = 0;
	cmd_i = ft_echo_builtin_find_cmd_i(exec_info->cmd, &n_flag);
	while (exec_info->cmd[cmd_i])
	{
		str[str_i] = exec_info->cmd[cmd_i];
		str_i++;
		cmd_i++;
	}
	ft_echo_builtin_print_str(str, n_flag);
	exit(EXIT_SUCCESS);
}
