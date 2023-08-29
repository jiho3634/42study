/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekpark <jeekpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:55:37 by jeekpark          #+#    #+#             */
/*   Updated: 2022/11/10 13:52:54 by jeekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	if ((unsigned char) c == '\0')
		return ((char *) &s[i]);
	return ((void *) 0);
}
