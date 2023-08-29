/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:30:42 by tnam              #+#    #+#             */
/*   Updated: 2023/08/29 12:50:15 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1
# define CHILD 0
# define IN 0
# define OUT 1
# define NONE -1

/* Global Variable */
extern int	g_child_exit_code;

/* List */
typedef struct s_node
{
	void			*content;
	struct s_node	*next_node;
	struct s_node	*prev_node;
}	t_node;

typedef struct s_list
{
	t_node			*front_node;
	t_node			*back_node;
	t_node			*cur_node;
}	t_list;

/* Token */
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

/* Program */
typedef struct s_info
{
	int				argc;
	char			**argv;
	char			**envp;
	t_list			mini_envp;
	struct termios	termios_backup;
	struct termios	termios;
}	t_info;

typedef struct s_parse
{
	char			*line;
	size_t			line_i;
	size_t			token_count;
	t_token			*tokens;
	size_t			tokens_i;
	t_token			*token;
	char			*temp_str;
	size_t			temp_str_len;
	size_t			start_i;
	size_t			str_i;
	int				squote_flag;
	int				dquote_flag;
	char			*target_env;
	char			*env_val;
	size_t			env_val_len;
	char			*old_str;
	char			*new_str;
	char			*exit_code;
}	t_parse;

typedef enum e_redirect_type
{
	OUT1,
	OUT2,
	IN1,
	HERE_DOC,
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*value;
}	t_redirect;

typedef struct s_exec_info
{
	char			*cmd_path;
	char			**cmd;
	size_t			cmd_i;
	t_redirect		*redirect;
	size_t			redirect_i;
	pid_t			pid;
	int				use_pipe;
	int				pipe_fd[2];
	int				infile_fd;
	int				outfile_fd;
	int				builtin_parent;
}	t_exec_info;

typedef struct s_exec
{
	t_exec_info	*exec_arr;
	size_t		exec_arr_size;
	size_t		exec_arr_i;
	int			prev_pipe_fd;
	char		**path_envp;
	pid_t		current_child_pid;
}	t_exec;

/* 0_init */
void	ft_init(int argc, char **argv, char **envp, t_info *info);
void	ft_sig_init(t_info *info);
void	ft_sig_for_here_doc_parent(int sig);
void	ft_sig_for_here_doc_child(int sig);
void	ft_sig_for_parent(int sig);
void	ft_mini_envp_init(char **envp, t_info *info);
int		ft_init_exec(t_info *info, t_parse *parse, t_exec *exec);

/* 1_parse */
int		ft_parse(t_info *info, t_parse *parse);
int		ft_count_token(t_parse *parse);
int		ft_tokenization(t_parse *parse);
int		ft_make_token(t_parse *parse, t_token_type type);
int		ft_convert_env(t_info *info, t_parse *parse);
int		ft_convert_child_exit_code(t_parse *parse);
void	ft_remove_quote(t_parse *parse);
int		ft_syntax_check(t_parse *parse);

/* 2_make_exec_info */
int		ft_make_exec_info(t_info *info, t_parse *parse, t_exec *exec);
int		ft_set_exec_info(t_parse *parse, t_exec_info *exec_info);

/* 3_exec */
int		ft_exec(t_info *info, t_parse *parse, t_exec *exec);
void	ft_exec_cmd(t_info *info, t_parse *parse,
			t_exec *exec, t_exec_info *exec_info);
int		ft_exec_builtin(t_info *info, t_parse *parse,
			t_exec *exec, t_exec_info *exec_info);
int		ft_exec_builtin_parent(t_info *info, t_parse *parse,
			t_exec *exec, t_exec_info *exec_info);
int		ft_check_here_doc(t_exec *exec);
void	ft_set_redirect_fd(t_exec_info *exec_info);
void	ft_set_pipe_fd(t_exec *exec, t_exec_info *exec_info);

/* 4_builtin */
int		ft_echo_builtin(t_exec_info *exec_info);
int		ft_cd_builtin(t_exec_info *exec_info);
int		ft_env_builtin(t_info *info);
int		ft_exit_builtin(t_list *mini_envp, t_parse *parse, t_exec *exec,
			t_exec_info *exec_info);
int		ft_export_builtin(t_info *info, t_exec_info *exec_info);
int		ft_pwd_builtin(void);
int		ft_unset_builtin(t_info *info, t_exec_info *exec_info);

/* ft_list */
t_list	ft_list_init(void);
int		ft_list_push_back(void *content, t_list *list);
int		ft_list_del_node(t_list *list, t_node *node);
void	ft_list_clear(t_list *list);

/* utils */
int		ft_error(char *msg, int error_code);
int		ft_perror(int error_code);
void	ft_cmd_is_directory(char *cmd_path);
int		ft_is_space(char c);
int		ft_is_operator(char c);
int		ft_is_redirect(char c);
int		ft_is_quote(char c);
int		ft_is_env(t_info *info, t_parse *parse);
int		ft_is_heredoc(char c1, char c2);
int		ft_is_child_exit_code(t_parse *parse);
int		ft_is_builtin(t_exec_info *exec_info);
int		ft_is_builtin_parent(t_exec *exec, t_exec_info *exec_info);
void	ft_free_tokens(t_parse *parse, size_t token_size);
void	ft_free_exec(t_exec *exec, size_t exec_info_size);
void	ft_free_all(t_parse *parse, t_exec *exec);

#endif
