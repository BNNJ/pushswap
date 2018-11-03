/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:20:10 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 20:20:35 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*(const unsigned char*)s1 == *(const unsigned char*)s2 && --n)
	{
		++s1;
		++s2;
	}
	return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}
