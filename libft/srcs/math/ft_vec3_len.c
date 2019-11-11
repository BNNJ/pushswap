/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:36:57 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 13:36:59 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_vec3_len(const t_vec3 *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}
