/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:37:45 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/11 15:31:21 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freemalloc(char ***res, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free((*res)[i]);
		i++;
	}
	free(*res);
	return ((void *) 0);
}

static int	ft_countstr(char const *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			cnt++;
		}
	}
	return (cnt);
}

static char	**ft_cutstr(char ***res, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		cnt = 0;
		while (s[i + cnt] && s[i + cnt] != c)
			cnt++;
		if (cnt == 0)
			return (*res);
		(*res)[j] = (char *) malloc(sizeof(char) * (cnt + 1));
		if ((*res)[j] == 0)
			return (ft_freemalloc(res, j));
		cnt = -1;
		while (s[i] && s[i] != c)
			(*res)[j][++cnt] = s[i++];
		(*res)[j][++cnt] = '\0';
		(*res)[++j] = (void *) 0;
	}
	return (*res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	res = (char **) malloc(sizeof(char *) * (ft_countstr(s, c) + 1));
	if (res == (void *) 0)
		return ((void *) 0);
	res[0] = (void *) 0;
	res = ft_cutstr(&res, s, c);
	return (res);
}
