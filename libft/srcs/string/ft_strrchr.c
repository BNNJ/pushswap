/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:37:12 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 20:37:14 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	char	x;

	x = (char)c;
	ret = NULL;
	while (*s)
	{
		if (*s == x)
			ret = (char*)s;
		++s;
	}
	return (ret);
}
