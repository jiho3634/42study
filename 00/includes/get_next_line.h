/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:21:56 by tnam              #+#    #+#             */
/*   Updated: 2023/03/02 14:28:33 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_gnl(char *contents, char *buffer);
char	*ft_strchr(const char *s, int c);
void	ft_make_line(char *line, char *contents, size_t line_len);
char	*ft_new_contents(char *new_contents, char *contents, size_t start);

#endif