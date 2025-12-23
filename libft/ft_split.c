/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2022/02/05 17:37:25 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	word_count(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i] != 0)
				i ++;
		}
		else
		{
			while (s[i] == c && s[i] != 0)
				i ++;
		}
	}
	return (j);
}

int	alloc_error(char **tab, int j)
{
	if (tab[j])
		return (0);
	while ((int long long)j >= 0)
	{
		free(tab[j]);
		j --;
	}
	free(tab);
	return (1);
}

void	alloc_and_cpy(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		if (s[i] != c)
		{
			while (s[i + n] != c && s[i + n] != 0)
				n ++;
			tab[j] = malloc(n + 1);
			if (alloc_error(tab, j))
				return ;
			ft_strlcpy(tab[j], (char *) &s[i], n + 1);
			i += n;
			j ++;
			n = 0;
		}
		while (s[i] == c && s[i] != 0)
			i ++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (tab == 0)
		return (0);
	tab[word_count(s, c)] = 0;
	alloc_and_cpy(tab, s, c);
	return (tab);
}
