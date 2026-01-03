/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 00:55:43 by pkorsako          #+#    #+#             */
/*   Updated: 2022/01/03 15:56:59 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long int n, int fd, int r)
{
	int long	m;
	int			i;

	i = 0;
	m = n;
	if (m < 0)
	{
		i = 1;
		ft_putchar_fd('-', fd);
		m *= -1;
	}
	if (m >= 10)
		r = ft_putnbr_fd(m / 10, fd, r);
	m %= 10;
	ft_putchar_fd(m + '0', fd);
	return (r + i + 1);
}

// void	ft_putnbr_fd(int n, int fd)
// {
// 	int long	m;

// 	m = n;
// 	if (m < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		m *= -1;
// 	}
// 	if (m >= 10)
// 		ft_putnbr_fd(m / 10, fd);
// 	m %= 10;
// 	ft_putchar_fd(m + '0', fd);
// }
