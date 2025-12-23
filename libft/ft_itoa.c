/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:36:51 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/05 17:24:20 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_invers(char *r)
{
	char	temp[12];
	int		i;

	i = 0;
	if (! ft_isdigit(r[0]))
	{
		r[i] = '0';
		r[i + 1] = 0;
	}
	else
	{
		while (r[i] != 0)
		{
			temp[i] = r[ft_strlen(r) - i - 1];
			i ++;
		}
		temp[i] = 0;
		i = 0;
		while (temp[i] != 0)
		{
			r[i] = temp[i];
			i ++;
		}
	}
}

size_t	ft_int_size(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i ++;
		n = n * -1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*r;
	long int	k;
	int			i;

	k = (long int)n;
	i = 0;
	r = malloc(ft_int_size(n) + 1);
	if (!r)
		return (NULL);
	if (k < 0 && ++i)
	{
		r[0] = '-';
		k = k * -1;
	}
	while (k != 0)
	{
		r[i ++] = (k % 10) + 48;
		k /= 10;
	}
	r[i] = 0;
	if (r[0] == '-')
		ft_invers(r + 1);
	else
		ft_invers(r);
	return (r);
}
