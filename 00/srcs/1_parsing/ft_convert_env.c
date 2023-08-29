/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:45:53 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 16:17:20 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_quote_flag(t_parse *parse)
{
	if (parse->token->str[parse->str_i] == '"'
		&& parse->dquote_flag == FALSE)
		parse->dquote_flag = TRUE;
	else if (parse->token->str[parse->str_i] == '"'
		&& parse->dquote_flag == TRUE)
		parse->dquote_flag = FALSE;
	if (parse->token->str[parse->str_i] == '\''
		&& parse->dquote_flag == FALSE
		&& parse->squote_flag == FALSE)
		parse->squote_flag = TRUE;
	else if (parse->token->str[parse->str_i] == '\''
		&& parse->dquote_flag == FALSE
		&& parse->squote_flag == TRUE)
		parse->squote_flag = FALSE;
}

static int	ft_check_env(t_info *info, t_parse *parse)
{
	parse->start_i = parse->str_i;
	while (ft_isalnum(parse->token->str[parse->str_i + 1])//알파벳이나 숫자
		|| parse->token->str[parse->str_i + 1] == '-'
		|| parse->token->str[parse->str_i + 1] == '_')
		parse->str_i++;
	parse->temp_str_len = parse->str_i - parse->start_i;
	parse->temp_str = (char *)ft_calloc(parse->temp_str_len, sizeof(char));
	if (parse->temp_str == NULL)
		return (ft_error("Failed malloc temp_str", FAILURE));
	ft_strlcpy(parse->temp_str, &parse->token->str[parse->start_i + 1],
		parse->temp_str_len + 1);
	parse->target_env = ft_strjoin(parse->temp_str, "=");
	if (parse->target_env == NULL)
	{
		free(parse->temp_str);
		return (ft_error("Failed ft_strjoin target_env", FAILURE));
	}
	free(parse->temp_str);
	if (ft_is_env(info, parse) == TRUE)
		return (TRUE);
	free(parse->target_env);
	return (FALSE);
}

static int	ft_add_env(t_parse *parse)
{
	parse->token->str[parse->start_i] = '\0';
	parse->old_str = ft_strjoin(parse->token->str, parse->env_val);
	if (parse->old_str == NULL)
	{
		free(parse->target_env);
		free(parse->env_val);
		return (ft_error("Failed ft_strjoin old_str", FAILURE));
	}
	parse->new_str
		= ft_strjoin(parse->old_str, &parse->token->str[parse->str_i + 1]);
	if (parse->new_str == NULL)
	{
		free(parse->target_env);
		free(parse->env_val);
		free(parse->old_str);
		return (ft_error("Failed ft_strjoin new_str", FAILURE));
	}
	free(parse->target_env);
	free(parse->env_val);
	free(parse->old_str);
	free(parse->token->str);
	parse->token->str = parse->new_str;
	return (SUCCESS);
}

static int	ft_find_env(t_info *info, t_parse *parse)
{//token 이 heredoc('<<')이 아니라면
	ft_set_quote_flag(parse);//qoute flag 켰다 껐다 함, quote가 열렸는지 닫혔는지 표시.
	if (parse->squote_flag == FALSE && parse->token->str[parse->str_i] == '$'//quote 닫혔고, $이고,
		&& (ft_isalpha(parse->token->str[parse->str_i + 1]) //다음문자가 알파벳
			|| parse->token->str[parse->str_i + 1] == '_'//or _
			|| parse->token->str[parse->str_i + 1] == '-'//or -
			|| parse->token->str[parse->str_i + 1] == '?'))//or ?이면
	{
		if (ft_is_child_exit_code(parse) == TRUE)//그 중에 ?이면
			return (ft_convert_child_exit_code(parse));//$?이므로 전에 썼던 str으로 대체하고 다음 문장을 이어줌
		else if (ft_check_env(info, parse) == TRUE)
		{
			if (ft_add_env(parse) == FAILURE)
				return (FAILURE);
			parse->str_i = parse->start_i + parse->env_val_len - 1;
		}
		else
		{
			ft_strlcpy(&parse->token->str[parse->start_i],
				&parse->token->str[parse->str_i + 1],
				ft_strlen(parse->token->str) + 1);
			parse->str_i -= parse->temp_str_len + 1;
		}
	}
	return (SUCCESS);
}

int	ft_convert_env(t_info *info, t_parse *parse)
{
	parse->tokens_i = 0;//초기화
	while (parse->tokens_i < parse->token_count)//token 모두 탐방
	{
		parse->token = &parse->tokens[parse->tokens_i];
		parse->str_i = 0;//초기화
		while (parse->token->str[parse->str_i])//token 한 str을 반복문으로 한글자씩 확인
		{
			if (ft_is_heredoc(parse->token->str[parse->str_i],
					parse->token->str[parse->str_i + 1]) == TRUE)//'<<'이라면
			{
				parse->tokens_i++;//ft_find_env 함수를 실행하지 않고 넘어감
				break ;
			}
			if (ft_find_env(info, parse) == FAILURE)
				return (FAILURE);
			parse->str_i++;
		}
		parse->tokens_i++;
	}
	return (SUCCESS);
}
