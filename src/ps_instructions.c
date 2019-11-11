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

/*
** The four stack instructions allowed :
** Swap : swaps the top two elements of a stack
** Push : pop the top element of a stack and pushs it to the other one
** rot : puts the top element of a stack at the bottom
** revrot : puts the bottom element of a stack at the top
*/

static void	ps_swap(t_ps *ps, uint8_t stack)
{
	t_psnode	*tmp;
	t_stack		*s;

	s = ps->stacks[stack];
	if (s->size > 1)
	{
		if (ps->opt & F_DEBUG)
			ft_dprintf(2, "# S%c : %d & %d\n", stack + 'A',
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
			ft_dprintf(2, "# P%c : %d\n", stack + 'A',
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
			ft_dprintf(2, "# R%c : %d\n", stack + 'A',
				ps->stacks[stack]->top->idx);
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
			ft_dprintf(2, "# RR%c : %d\n", stack + 'A',
				ps->stacks[stack]->top->idx);
		s->top = s->top->next;
	}
}

/*
** Wrapper around those instructions, to make instruction calling simpler.
** s : the stack on which the instruction is to be applied
** instcode : the instruction code as defined in the header file
**
** If the F_SAVE flag is set, the instruction is not only executed,
** but also added to the instruction list.
*/

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
