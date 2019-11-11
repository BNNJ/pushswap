/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:21:43 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 15:21:46 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int		ft_atoi_v(const char *str, int *ret)
{
	short		sign;
	long long	result;
	int			len;

	len = 0;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	sign = (*str == '-' || *str == '+') ? -(*str++ - 44) : 1;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - '0');
		++len;
	}
	result *= sign;
	if (len > 11 || result < INT_MIN || result > INT_MAX)
		return (0);
	*ret = result;
	return (1);
}
