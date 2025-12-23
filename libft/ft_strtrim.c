/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:52:12 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/05 17:43:06 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	start_s1(char const *s1, char const *set)
{
	size_t	ss1;
	size_t	j;

	ss1 = 0;
	j = 0;
	while (set[j] != 0)
	{
		if (s1[ss1] == set[j])
		{
			ss1 ++;
			j = -1;
		}
		j ++;
	}
	return (ss1);
}

size_t	end_s1(char const *s1, char const *set, size_t es1)
{
	size_t	j;

	j = 0;
	while (set[j] != 0)
	{
		if (s1[es1 - 1] == set[j])
		{
			es1 --;
			j = -1;
		}
		j ++;
	}
	return (es1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	ss1;
	size_t	es1;
	char	*r;
	int		u;

	ss1 = start_s1(s1, set);
	es1 = end_s1(s1, set, ft_strlen(s1));
	u = es1 - ss1;
	if (u < 0)
		r = malloc(1);
	else
		r = malloc(es1 - ss1 + 1);
	if (r == 0)
		return (0);
	if (u < 0)
	{
		ft_strlcpy(r, "", 1);
		return (r);
	}
	ft_strlcpy(r, s1 + ss1, es1 - ss1 + 1);
	return (r);
}
