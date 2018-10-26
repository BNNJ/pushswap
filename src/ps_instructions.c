/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:21:37 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:21:38 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ps_swap(t_ps *ps, uint8_t stack)
{
	t_psnode	*tmp;
	t_stack		*s;

	s = ps->stacks[stack];
	if (s->size > 1)
	{
		if (ps->opt & F_DEBUG)
			ft_printf("# S%c : %d & %d\n", stack + 'A',
				ps->stacks[stack]->top->idx, ps->stacks[stack]->top->prev->idx);
		tmp = ft_pop(s);
		s->top = s->top->prev;
		ft_push(s, tmp);
		s->top = s->top->next;
	}
}

static void	ps_push(t_ps *ps, uint8_t stack)
{
	t_stack	*from;
	t_stack	*to;

	to = ps->stacks[stack];
	from = ps->stacks[stack ^ 1];
	if (from->size > 0)
	{
		if (ps->opt & F_DEBUG)
			ft_printf("# P%c : %d\n", stack + 'A',
				ps->stacks[stack ^ 1]->top->idx);
		ft_push(to, ft_pop(from));
	}
}

static void	ps_rot(t_ps *ps, uint8_t stack)
{
	t_stack	*s;

	s = ps->stacks[stack];
	if (s->size > 1)
	{
		if (ps->opt & F_DEBUG)
			ft_printf("# R%c : %d\n", stack + 'A', ps->stacks[stack]->top->idx);
		s->top = s->top->prev;
	}
}

static void	ps_revrot(t_ps *ps, uint8_t stack)
{
	t_stack	*s;

	s = ps->stacks[stack];
	if (s->size > 1)
	{
		if (ps->opt & F_DEBUG)
			ft_printf("# RR%c : %d\n", stack + 'A',
				ps->stacks[stack]->top->idx);
		s->top = s->top->next;
	}
}

void		ps_inst(t_ps *ps, uint8_t s, int instcode)
{
	static t_inst	inst[4] = {
		[PUSH] = ps_push,
		[SWAP] = ps_swap,
		[ROT] = ps_rot,
		[REVROT] = ps_revrot
	};

	if (s < 2)
		inst[instcode](ps, s);
	else
	{
		inst[instcode](ps, 0);
		inst[instcode](ps, 1);
	}
	if (ps->opt & F_SAVE)
		if (!(add_node(ps->op, instcode * 3 + s)))
			ps_exit(ps, "Error : problem adding instruction\n", EXIT_FAILURE);
}
