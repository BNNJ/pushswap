/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:22:48 by pfragnou          #+#    #+#             */
/*   Updated: 2019/04/16 20:22:49 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpn_calc.h"
#include <stdlib.h>

void		push(t_rpn_stack *s, t_rpn_node *op)
{
	if (op)
	{
		if (s->size == 0)
		{
			s->bot = op;
			s->top = op;
		}
		else
		{
			op->prev = s->top;
			s->top->next = op;
			s->top = op;
		}
		++s->size;
	}
}

void		push_back(t_rpn_stack *s, t_rpn_node *op)
{
	if (op)
	{
		if (s->size == 0)
		{
			s->top = op;
			s->bot = op;
		}
		else
		{
			op->next = s->bot;
			s->bot->prev = op;
			s->bot = op;
		}
		++s->size;
	}
}

t_rpn_node	*pop(t_rpn_stack *s)
{
	t_rpn_node	*op;

	if (s->size == 0)
		op = NULL;
	else
	{
		op = s->top;
		s->top = s->top->prev;
		if (s->top)
			s->top->next = NULL;
		op->prev = NULL;
		--s->size;
	}
	return (op);
}

int			pop_f(t_rpn_stack *s)
{
	t_rpn_node	*tmp;
	int			val;

	if ((tmp = pop(s)))
	{
		val = tmp->val;
		free(tmp);
		return (val);
	}
	return (0);
}

t_rpn_node	*new_node(int type, int val)
{
	t_rpn_node	*op;

	if (!(op = malloc(sizeof(t_rpn_node))))
		return (NULL);
	op->val = val;
	op->type = type;
	op->next = NULL;
	op->prev = NULL;
	return (op);
}
