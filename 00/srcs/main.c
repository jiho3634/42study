/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:30:14 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 12:50:06 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* print test function */
void	print_tokens(t_parse *parse)
{
	char	*type;

	printf("\n=========\n");
	for (size_t i = 0; i < parse->token_count; i++)
	{
		if (parse->tokens[i].type == WORD)
			type = "WORD";
		if (parse->tokens[i].type == PIPE)
			type = "PIPE";
		if (parse->tokens[i].type == REDIRECT)
			type = "REDIRECT";
		printf("Token%zu type = %s\n", i + 1, type);
		printf("Token%zu str = %s\n", i + 1, parse->tokens[i].str);
		printf("---------\n");
	}
	printf("=========\n\n");
}

/* print test function */
void	print_exec(t_exec *exec)
{
	printf("\n=========\n");
	for (size_t i = 0; i < exec->exec_arr_size; i++)
	{
		printf("cmd_path = %s\n", exec->exec_arr[i].cmd_path);
		for (size_t j = 0; exec->exec_arr[i].cmd[j] != NULL; j++)
		{
			printf("cmd[%zu] = %s\n", j, exec->exec_arr[i].cmd[j]);
		}
		printf("---------\n");
		for (size_t j = 0; ; j++)
		{
			if (exec->exec_arr[i].redirect[j].value == 0)
				break ;
			printf("redirect[%zu].type = %u\n", j, exec->exec_arr[i].redirect[j].type);
			printf("redirect[%zu].value = %s\n", j, exec->exec_arr[i].redirect[j].value);
		}
		printf("---------\n");
	}
	printf("=========\n\n");
}

void leaks() // memory leak test
{
	system("leaks -q $PPID");
}

static void	ft_parse_execute(t_info *info, t_parse *parse, t_exec *exec)
{
	if (ft_parse(info, parse) == FAILURE)
		return ;
	if (ft_make_exec_info(info, parse, exec) == FAILURE)
		return ;
	if (ft_exec(info, parse, exec) == FAILURE)
		return ;
	//print_tokens(parse); // test
	//print_exec(exec); // test
	ft_free_all(parse, exec);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info		info;
	t_parse		parse;
	t_exec		exec;

	ft_init(argc, argv, envp, &info);//터미널 설정 백업, 환경변수 복사
	while (TRUE)
	{
		ft_sig_init(&info);//터미널 제어문자 에코 비활성화, 시그널함수 사용
		parse.line = readline("\033[0;35mwhine 🍷 ");
		if (parse.line == NULL)
		{
			ft_list_clear(&info.mini_envp);
			ft_putstr_fd("\x1b[1A\033[9Cexit\n", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
		if (parse.line[0] == '\0')
		{
			free(parse.line);
			continue ;
		}
		add_history(parse.line);
		ft_parse_execute(&info, &parse, &exec);
		free(parse.line);
	}
	return (EXIT_SUCCESS);
}
