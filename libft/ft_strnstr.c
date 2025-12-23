/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:54:37 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/03 16:11:32 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[j] != 0 && j < len)
	{
		i = 0;
		while (haystack[j + i] == needle[i] && i + j < len)
		{
			i++;
			if (needle[i] == '\0' && len != 0)
				return ((char *) &haystack[j]);
		}
		j++;
	}
	return (0);
}
