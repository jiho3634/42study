/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:25:09 by jihokim2          #+#    #+#             */
/*   Updated: 2022/12/23 14:31:06 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	exception(int fd)
{
	if (fd < 0)
		return (NULL);
}

t_list	*lst_set(t_list *lst, int fd)
{
	t_list	*new;

	if (!lst)
		lst = ft_lstnew(fd);
	while (lst -> fd != fd)
	{
		if (lst -> next == NULL)
		{
			new = ft_lstnew(fd);
			ft_lstadd_back(&lst, new);
		}
		lst = lst -> next;
	}
	return (lst);
}

void	check_remain(t_list *lst, char *line)
{
	// lst -> remain 에 남아있는 문자나 개행이 있는지 확인
	// ? lst -> remain 이 NULL 인지로 판단해보자
	if (lst -> remain)
	{
		// 문자나 개행이 있는 경우 line에 복사하고 초기화
		// ? 그냥 할당만 해도 되는지 모르겠다. memcpy같은 걸 해야하나?
		line = lst -> remain;
		free (lst -> remain);
	}
}

int	check_line(char *line)
{
	char	*temp;

	// line 에 문자가 있는지 확인
	// remain 에 문자가 없었다면 line = NULL
	if (line)
	{
		// 문자만 있는지, 개행까지 있는지 체크
		temp = strchr(line, '\n');
		// 개행까지 있다면,
		if (temp)
		{
			// 개행 뒤가 '\0' 이 아닐 때 
			if (*(++temp))
			{
				// lst -> remain 에 개행 뒤부터 strdup
				lst -> remain = ft_strdup(temp + 1);
				// 개행까지 line에 남기고 개행 뒤는 '\0'
				*temp = 0;
			// 개행 뒤가 '\0'이면 return (line);
			else
				return (0);
		}
		// 문자만 있다면, get_line;
	}
	return (1);
}

void	get_line(int fd, t_list *lst, char *line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	ret;

	//read 해서 line에 추가한다.
	//read(fd, buf, BUFFER_SIZE);
	ret = read(fd, buf, BUFFER_SIZE);
	//read의 return 값이 -1 or EOF이면, return ;
	//ret < 0 이면 read 에러 -> 싹다 정리하고 NULL 반환?
	// ret = 0 이면 파일이 비었거나 EOF -> return (NULL);
	if (ret <= 0)
	{
		//lst -> remain에 문자가 남아있으면 프리못해
		if (lst -> remain == NULL)
		{
			if (lst -> prev != NULL)
				(lst -> prev) -> next = lst -> next;
			if (lst -> next != NULL)
				(lst -> next) -> prev = lst -> prev;
			free (lst);
		}
		//line 에 문자만 있어서 return (line) 해야함
		return ;
	}
	// 0 < ret < BUFFER_SIZE -> 막타침 buf[ret] = 0;
	else if (ret > 0 && ret < BUFFER_SIZE)
	
	// ret = BUFFER_SIZE -> 정상 line에 strjoin
	// 인자로 받은 line은 strjoin후에 free해줘야함
	else
	{
		temp = ft_strjoin(line, buf);
		free(line);
		line = temp;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	exception(fd);
	set_lst(lst, fd);
	check_remain(lst);
	while (check_line(line))
		get_line(fd, lst, line);
	return (line);
}
