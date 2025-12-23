/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:28:24 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/03 16:14:10 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*r;
	unsigned int	i;

	i = 0;
	r = malloc(ft_strlen(s) + 1);
	if (r == 0)
		return (0);
	while (s[i] != 0)
	{
		r[i] = f(i, s[i]);
		i ++;
	}
	r[i] = 0;
	return (r);
}
