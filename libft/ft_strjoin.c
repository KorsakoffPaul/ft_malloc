/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:46:48 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/03 16:13:13 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dest == 0)
		return (0);
	ft_strlcpy(dest, s1, ft_strlen(s1) + 1);
	ft_strlcpy(dest + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (dest);
}
