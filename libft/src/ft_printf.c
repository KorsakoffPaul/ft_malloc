/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:35:40 by pkorsako          #+#    #+#             */
/*   Updated: 2022/04/06 15:19:17 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	hexa_convert(long int i, int y)
{
	if (i >= 0 && i <= 9)
		return (i + 48);
	if (i > 9)
		return (i - 10 + y);
	return (0);
}

int	print_hexa_convert(unsigned long int i, int y, char *s)
{
	char	convert_num[20];
	int		p;
	int		r;

	ft_bzero(convert_num, 20);
	p = 18;
	if (!s)
		i = (unsigned int) i;
	if (i == 0)
	{
		convert_num[p] = hexa_convert(i % 16, y);
		p --;
	}
	while (i > 0)
	{	
		convert_num[p] = hexa_convert(i % 16, y);
		p --;
		i /= 16;
	}
	if (s)
		ft_putstr_fd(s, 1);
	ft_putstr_fd(convert_num + p + 1, 1);
	r = ft_strlen(convert_num + p + 1);
	return (r);
}

int	check_args(va_list args, const char *s, int i)
{
	int	r;

	if (s[i] == 'c')
		r = ft_putchar_fd(va_arg(args, int), 1);
	if (s[i] == 's')
		r = ft_putstr_fd(va_arg(args, char *), 1);
	if (s[i] == 'p')
		r = print_hexa_convert(va_arg(args, unsigned long int), 'a', "0x") + 2;
	if (s[i] == 'd')
		r = ft_putnbr_fd(va_arg(args, int), 1, 0);
	if (s[i] == 'i')
		r = ft_putnbr_fd(va_arg(args, int), 1, 0);
	if (s[i] == 'u')
		r = ft_putnbr_fd(va_arg(args, unsigned int), 1, 0);
	if (s[i] == 'x')
		r = print_hexa_convert(va_arg(args, int), 'a', NULL);
	if (s[i] == 'X')
		r = print_hexa_convert(va_arg(args, int), 'A', NULL);
	if (s[i] == '%')
		r = ft_putchar_fd('%', 1);
	return (r);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		r;
	va_list	args;

	i = 0;
	r = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] != '%')
		{
			r ++;
			ft_putchar_fd(s[i], 1);
		}
		else if (s[i] == '%')
		{
			r += check_args(args, s, i + 1);
			i ++;
		}
		i ++;
	}
	va_end(args);
	return (r);
}
