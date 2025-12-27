/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:36:32 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/03 16:08:28 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	j;

	j = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (*(s + i) == j)
			return ((char *)s + i);
		i --;
	}
	return (0);
}
