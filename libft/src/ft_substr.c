/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:21:20 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/03 16:12:51 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	while (*s && start)
	{
		s++;
		start--;
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, len + 1);
	return (dest);
}
