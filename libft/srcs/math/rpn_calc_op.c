/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:22:36 by pfragnou          #+#    #+#             */
/*   Updated: 2019/04/16 20:22:37 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		op_add(int b, int a, int *ret)
{
	*ret = a + b;
	return (1);
}

int		op_sub(int b, int a, int *ret)
{
	*ret = a - b;
	return (1);
}

int		op_mul(int b, int a, int *ret)
{
	*ret = a * b;
	return (1);
}

int		op_div(int b, int a, int *ret)
{
	if (b == 0)
		return (0);
	*ret = a / b;
	return (1);
}

int		op_mod(int b, int a, int *ret)
{
	if (b == 0)
		return (0);
	*ret = a % b;
	return (1);
}
