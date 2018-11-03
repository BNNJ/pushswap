/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:51:41 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 18:51:46 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (dst > src)
		while (n--)
			*(unsigned char*)(dst + n) = *(unsigned char*)(src + n);
	else if (dst < src)
		ft_memcpy(dst, src, n);
	return (dst);
}
