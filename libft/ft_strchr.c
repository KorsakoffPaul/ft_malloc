/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:39:49 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/05 16:23:45 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	j;

	i = 0;
	j = (char)c;
	while (i < ft_strlen(s))
	{
		if (*(s + i) == j)
			return (((char *)s + i));
		i ++;
	}
	if (*(s + i) == j)
		return (((char *)s + i));
	return (0);
}
