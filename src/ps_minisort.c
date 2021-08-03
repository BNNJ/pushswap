/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_minisort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:27:02 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:27:03 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Flips a stack upside down, in case it's sorted in the wrong order.
*/

void				ps_revsort(t_ps *ps)
{
	while (ps->stacks[0]->size > 3)
	{
		ps_inst(ps, 0, REVROT);
		ps_inst(ps, 1, PUSH);
	}
	ps_threesort(ps, 0, ps->stacks[0]->size);
	while (ps->stacks[1]->size)
		ps_inst(ps, 0, PUSH);
}

/*
** Sorts 3 values in maximum 2 instructions, if the stack is otherwise empty.
*/

void				ps_threesort(t_ps *ps, uint8_t s, size_t size)
{
	t_stack	*a;

	a = ps->stacks[s];
	if (size == 3)
		while (!(a->top->idx < a->top->prev->idx
			&& a->top->prev->idx < a->top->next->idx))
		{
			if (a->top->prev->idx > a->top->idx
				&& a->top->prev->idx > a->top->next->idx)
				ps_inst(ps, s, REVROT);
			else if (a->top->prev->idx < a->top->idx
				&& a->top->prev->idx > a->top->next->idx)
				ps_inst(ps, s, ROT);
			else if (a->top->prev->idx < a->top->idx
				&& a->top->idx < a->top->next->idx)
				ps_inst(ps, s, SWAP);
			else if (a->top->prev->idx < a->top->idx
				&& a->top->idx > a->top->next->idx)
				ps_inst(ps, s, ROT);
		}
	else if (size == 2 && a->top->idx > a->top->prev->idx)
		ps_inst(ps, s, SWAP);
}

/*
** Sorts A for partitions of size 3 or less.
** Best case is 0 instructions for an already sorted partition,
** worst case is 5 instructions for revsorted paritions.
*/

static void			ps_minisort_a(t_ps *ps, size_t size)
{
	if (size == 2 && ps->stacks[0]->top->idx > ps->stacks[0]->top->prev->idx)
		ps_inst(ps, 0, SWAP);
	else if (size == 3)
	{
		if (ps->stacks[0]->top->prev->idx < ps->stacks[0]->top->prev->prev->idx
			&& ps->stacks[0]->top->idx < ps->stacks[0]->top->prev->idx)
			return ;
		else if (ps->stacks[0]->top->idx > ps->stacks[0]->top->prev->idx)
		{
			if (ps->stacks[1]->top->idx < ps->stacks[1]->top->prev->idx)
				ps_inst(ps, 2, SWAP);
			else
				ps_inst(ps, 0, SWAP);
		}
		else
		{
			ps_inst(ps, 0, ROT);
			ps_minisort_a(ps, size - 1);
			ps_inst(ps, 0, REVROT);
		}
		return (ps_minisort_a(ps, size));
	}
}

/*
** Sorts a partition on B of size 3 or less and pushes it to A
** (not necessarily in that order).
** Should be between 3 instructions for best case
** (top > prev > prev->prev)
** and 6 instructions for worst case (top < prev < prev->prev)
*/

static void			ps_minisort_b(t_ps *ps, size_t size)
{
	if (size == 1)
	{
		if (ps->stacks[0]->top->idx > ps->stacks[0]->top->prev->idx)
			ps_inst(ps, 0, SWAP);
		ps_inst(ps, 0, PUSH);
	}
	else
	{
		if (ps->stacks[1]->top->idx < ps->stacks[1]->top->prev->idx)
		{
			if (ps->stacks[0]->top->idx > ps->stacks[0]->top->prev->idx)
				ps_inst(ps, 2, SWAP);
			else
				ps_inst(ps, 1, SWAP);
		}
		ps_inst(ps, 0, PUSH);
		return (ps_minisort_b(ps, size - 1));
	}
}

/*
** Redirects to the proper algorithm to sort partitions of size 3 or less.
** The algorithm used depends on the stack to sort, and the presence or absence
** of other values (that should not be touched) in the stack.
*/

void				ps_minisort(t_ps *ps, uint8_t s, size_t size)
{
	t_stack	*a;

	a = ps->stacks[s];
	if (s == 0)
		size != a->size ? ps_minisort_a(ps, size)
			: ps_threesort(ps, s, size);
	else
		ps_minisort_b(ps, size);
}
