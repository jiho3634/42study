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
#include <stdio.h>
#include "get_next_line.h"

int	exception(int fd, t_list **lst)
{
	// fd가 음수인건 이해가 되는데 3은 왜 안되는지 이해가 안된다.
	if (fd < 0)
	{
		if (*lst)
		{
			free (*lst);
			*lst = 0;
		}
		return (-1);
	}
	return (0);
}

t_list	*set_lst(t_list *lst, int fd)
{
	t_list	*new;

	printf("before set_lst lst : %p\n", lst);
	if (!lst)
		lst = ft_lstnew(fd);
	printf("ft_lstnew lst : %p\n", lst);
	printf("lst -> fd : %d, fd : %d\n", lst -> fd, fd);
	while (lst -> fd != fd)
	{
		if (lst -> next == NULL)
		{
			new = ft_lstnew(fd);
			ft_lstadd_back(&lst, new);
		}
		lst = lst -> next;
	}
	printf("after set_lst lst : %p\n", lst);
	return (lst);
}

void	check_remain(t_list **lst, char **line)
{
	// lst -> remain 에 남아있는 문자나 개행이 있는지 확인
	// ? lst -> remain 이 NULL 인지로 판단해보자
	printf("check_remain, lst -> remain : %s\n", (*lst)-> remain);
	if ((*lst)-> remain != NULL)
	{
		// 문자나 개행이 있는 경우 line에 복사하고 초기화
		// ? 그냥 할당만 해도 되는지 모르겠다. memcpy같은 걸 해야하나?
		printf("if (check_remain != NULL) -> line : %p\n", *line);
		*line = (*lst)-> remain;
		free ((*lst)-> remain);
	}
}

int	check_line(t_list **lst, char **line)
{
	char	*temp;

	// line 에 문자가 있는지 확인
	// remain 에 문자가 없었다면 line = NULL
	printf("check_line line: %p\n", *line);
	if (*line)
	{
		// 문자만 있는지, 개행까지 있는지 체크
		temp = ft_strchr(*line, '\n');
		printf("check_line ft_strchr temp : %p\n", temp);
		// 개행까지 있다면,
		if (temp)
		{
			// 개행 뒤가 '\0' 이 아닐 때
			printf("check_line, if(temp), *(temp + 1) : %c\n", *(temp + 1));
			if (*(++temp))
			{
				// lst -> remain 에 개행 뒤부터 strdup
				// 개행 뒤에 널이 찍혀서 복사된다.
				// line의 개행 뒤에 널을 찍어서 return (0) -> return (line);
				// get_line에 갔다가 eof라서 다시 돌아온다면 바로 함수 종료된다.
				(*lst)-> remain = ft_strdup(temp);
				printf("check_line,(*lst)-> remain : %p\n", (*lst)-> remain);
				*temp = 0;
			}
			// 개행 뒤가 '\0'이면 return (line);
			return (0);
		}
		// 개행이 없다면, get_line;
	}
	return (1);
}

int	get_line(int fd, t_list **lst, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	ret;

	//read 해서 line에 추가한다.
	//read(fd, buf, BUFFER_SIZE);
	ret = read(fd, buf, BUFFER_SIZE);
	printf("get_line ret : %zd\n", ret);
	//read의 return 값이 -1 or EOF이면, return ;
	//ret < 0 이면 read 에러 -> 싹다 정리하고 NULL 반환?
	if (ret < 0)
	{
		// 그동안 read 한 것을 remain에 저장해놓고 NULL을 반환해야한다.
		if (*line)
		{
			(*lst)-> remain = ft_strdup(*line);
			free (*line);
		}
		return (0);
	}	
	//ret = 0 이면 파일이 비었거나 EOF -> return (NULL);
	else if (ret == 0)
	{
		//함수를 종료해야한다.
		//앞에서 생성한 리스트를 제거해야한다.
		//그전에 앞 뒤 리스트를 연결해주고 프리해주자
		//lst -> remain에 문자가 남아있으면 line 프리하지 말고 return (line);
		printf("get_line lst : %p\n", *lst);
		printf("get_line lst -> remain : %p\n", (*lst)-> remain);
		if ((*lst)-> remain == NULL)
		{
			printf("get_line lst -> prev : %p\n", (*lst)-> prev);
			if ((*lst)-> prev != NULL)
				((*lst)-> prev) -> next = (*lst)-> next;
			printf("get_line lst -> next : %p\n", (*lst)-> next);
			if ((*lst)-> next != NULL)
				((*lst)-> next) -> prev = (*lst)-> prev;
			free (*lst);
			*lst = 0;
		}
		//line 에 문자만 있어서 return (line) 해야함
		//종료조건을 어떻게 만들어 줘야할까
		//check_line으로 보내서 종료시키고 싶은데 어떻게하지????
		//check_line에서는 개행이 없으면 get_line 이고
		//개행이 있으면 뒤에 널을 체크하여 넣어주고 종료시킨다.
		//read하거나 join하거나 dup하는 과정에서 뒤에 널이 찍힌다.
		//종료조건을 널로 할 수 없다. 여기서 끝내야할 것 같다.
		printf("get_line *line : %p\n", *line);
		printf("get_line *lst : %p\n", *lst);
		return (0);
	}
	// 0 < ret < BUFFER_SIZE -> 막타침 buf[ret] = 0;
	// buf[ret] 이면 항상 문자의 뒤에 널이 찍힌다.
	// buf에서 line으로 join해주고 check_line으로 보내자
	// 개행이 있으면 check_line에서 끝나고 없으면 다시 get_line와서 끝난다.
	else
	{
		buf[ret] = '\0';
		printf("get_line buf[ret] : %s\n", buf);
		temp = ft_strjoin(*line, buf);
		printf("get_line temp : %p\n", temp);
		printf("get_line, before free *line : %p\n", *line);
		if (*line != 0)
			free (*line);
		*line = temp;
		printf("get_line line : %p\n", *line);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (exception(fd, &lst))
		return (NULL);
	lst = set_lst(lst, fd);
	line = 0;
	check_remain(&lst, &line);
	while (check_line(&lst, &line) != 0)
	{
		if (get_line(fd, &lst, &line) == 0)
			break;
	}
	return (line);
}
