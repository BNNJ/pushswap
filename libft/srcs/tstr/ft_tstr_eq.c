/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_eq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 04:47:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 04:47:08 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tstr_eq(const t_string *s1, const t_string *s2)
{
	return (ft_tstr_cmp(s1, s2) == 0);
}