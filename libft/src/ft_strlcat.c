/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:33:33 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/05 16:43:39 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	r;
	size_t	i;

	i = 0;
	r = ft_strlen(dest);
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != 0 && (r + i) < size - 1)
	{
		dest[r + i] = src[i];
		i ++;
	}
	dest[r + i] = 0;
	if (size > r)
		size = r;
	return (ft_strlen(src) + size);
}
