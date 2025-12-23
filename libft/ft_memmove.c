/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:48:07 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/05 16:16:23 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	if (src > dest)
		ft_memcpy(dest, src, n);
	else
	{
		i = n;
		while (i-- > 0)
			*((char *)dest + i) = *((char *)src + i);
	}
	return (dest);
}
