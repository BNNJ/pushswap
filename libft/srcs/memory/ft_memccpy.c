/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:54:43 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/05 15:54:49 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		dst = (unsigned char*)dst + 1;
		if (*(unsigned char*)src == (unsigned char)c)
			return (dst);
		src = (unsigned char*)src + 1;
	}
	return (NULL);
}
