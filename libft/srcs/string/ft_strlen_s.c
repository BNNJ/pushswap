/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:12:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/03 19:13:26 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen_s(const char *s)
{
	size_t len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		++len;
	return (len);
}
