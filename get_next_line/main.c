/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:40:51 by jihokim2          #+#    #+#             */
/*   Updated: 2022/12/26 16:24:10 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	buf[1];
	ssize_t	ret;

	fd = open("test.txt", O_RDONLY);
	ret = read(fd, buf, 1);
	printf("%zd\n", ret);
	ret = read(fd, buf, 1);
	printf("%zd\n", ret);
	ret = read(fd, buf, 1);
	printf("%zd\n", ret);
	ret = read(fd, buf, 1);
	printf("%zd\n", ret);

//	printf("line1 : %s", get_next_line(fd));
//	printf("line2 : %s", get_next_line(fd));
//	printf("line3 : %s", get_next_line(fd));
//	printf("line4 : %s", get_next_line(fd));
//	printf("line5 : %s", get_next_line(fd));
//	printf("line6 : %s", get_next_line(fd));
	close (fd);
	return (0);
}
