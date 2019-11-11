/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:32:39 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/05 18:32:41 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
static int	word_count(char const *s, char c)
{
	int		wc;

	wc = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			++wc;
		++s;
	}
	return (wc);
}

static void	*ft_strsplit_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		++i;
	}
	free(tab);
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	l;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (word_count(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		l = 0;
		while (*s == c && *s)
			++s;
		while (s[l] != c && s[l])
			++l;
		if (l != 0)
			if (!(tab[i++] = ft_strsub(s, 0, l)))
				return (ft_strsplit_free(tab));
		s += l;
	}
	tab[i] = 0;
	return (tab);
}
*/

char	**ft_strsplit(const char *str, char c)
{
	static int	i = 0;
	char		**arr;
	int			l;

	l = 0;
	while (*str == c)
		++str;
	while (str[l] && str[l] != c)
		++l;
	++i;
	if (!(arr = l == 0 ? malloc(sizeof(char*) * i) : ft_strsplit(str + l, c)))
		return (NULL);
	if (l == 0)
		arr[--i] = NULL;
	else if (!(arr[--i] = malloc(sizeof(char) * l)))
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
		return (NULL);
	}
	l ? arr[i][l] = 0 : 0;
	while (--l >= 0)
		arr[i][l] = str[l];
	return (arr);
}
