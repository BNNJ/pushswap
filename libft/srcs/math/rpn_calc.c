/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:22:06 by pfragnou          #+#    #+#             */
/*   Updated: 2019/04/16 20:22:07 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"
#include "stdlib.h"

t_rpnfunc	g_optab[5] = {&op_add, &op_sub, &op_mul, &op_div, &op_mod};

static int	rpn_error(t_rpn_stack *a, t_rpn_stack *b,
	t_rpn_node *op, int err_code)
{
	free(op);
	while (a->size > 0)
		pop_f(a);
	while (b->size > 0)
		pop_f(b);
	return (err_code);
}

int			rpn_calc(t_rpn_stack *s, int *ret)
{
	t_rpn_stack	tmp;
	t_rpn_node	*op;

	tmp = (t_rpn_stack){NULL, NULL, 0};
	while (s->size > 0)
	{
		while (s->top && s->top->type != T_OP)
			push(&tmp, pop(s));
		op = pop(s);
		if (tmp.size < 2)
			return (rpn_error(s, &tmp, op, 1));
		if (!g_optab[op->val](pop_f(&tmp), pop_f(&tmp), ret))
			return (rpn_error(s, &tmp, op, 2));
		op->val = *ret;
		op->type = T_VAL;
		push(&tmp, op);
	}
	*ret = pop_f(&tmp);
	if (tmp.size > 0 || s->size > 0)
		return (rpn_error(s, &tmp, op, 1));
	return (0);
}
