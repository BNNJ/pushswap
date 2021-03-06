/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 01:43:14 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 01:43:16 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	ft_vec3_new(const double x, const double y, const double z)
{
	return ((t_vec3){x, y, z});
}
