/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 00:27:05 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/03 16:14:35 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


int	ft_putstr_fd(char *c, int fd)
{
	int	r;

	if (c)
	{
		r = ft_strlen(c);
		while (*c != 0)
		{
			ft_putchar_fd(*c, fd);
			c ++;
		}
		return (r);
	}
	else
		ft_putstr_fd("(null)", 1);
	return (6);
}

// void	ft_putstr_fd(char *c, int fd)
// {
// 	int	i;

// 	i = 0;
// 	while (c[i] != 0)
// 	{
// 		ft_putchar_fd(c[i], fd);
// 		i ++;
// 	}
// }
