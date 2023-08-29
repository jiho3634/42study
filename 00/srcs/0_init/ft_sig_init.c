/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:23:33 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 11:11:26 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_2(int sig)
{
	(void)sig;
	g_child_exit_code = 1;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ft_sig_init(t_info *info)
{
	info->termios = info->termios_backup;//나중에 복구할 백업을 남겨둠
	info->termios.c_lflag = ~ECHOCTL;
	//c_lflag는 터미널 입력 모드를 제어하는 로컬 플래그를 보관
	//ECHOCTL은 제어 문자를 에코(반사)하는 것을 활성화 
	//~ECHOCTL은 비트를 반전시켜 제어 문자의 에코를 비활성화
	tcsetattr(STDIN_FILENO, TCSANOW, &info->termios);
	//TCSANOW는 터미널 속성을 즉시 변경하도록 지시하는 플래그입니다.
	signal(SIGINT, ft_signal_2);//SIGINT = 2, Ctrl + c -> 개행
	signal(SIGQUIT, SIG_IGN);//SIGQUIT = 3, SIG_IGN은 신호 무시
}

void	ft_sig_for_here_doc_parent(int sig)
{
	(void)sig;
	printf("\n");
}

void	ft_sig_for_here_doc_child(int sig)
{
	(void)sig;
	exit(1);
}

void	ft_sig_for_parent(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
	}
	if (sig == SIGQUIT)
	{
		printf("^\\Quit: %d\n", sig);
	}
}
