/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_opti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:35:03 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:35:04 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Processes the instructions list to try and make it shorter.
** It does so by removing two consecutive opposite instructions,
** or combining instructions that can be coupled.
** For exemple, if an RA instruction follows an RB instruction,
** they can be conbined into a single RR instruction.
*/

static t_psnode			*ps_optipush(t_ps *ps, t_psnode *cur, t_psnode *end)
{
	if (cur->prev->val - cur->val == 1 || cur->val - cur->prev->val == 1)
	{
		remove_node(ps->op, cur->prev);
		cur = remove_node(ps->op, cur);
		if (cur == end)
		{
			cur = cur->prev;
			ps->op->top = cur;
		}
		return (cur);
	}
	else
		return (cur->prev);
}

static t_psnode			*ps_optiswap(t_ps *ps, t_psnode *cur, t_psnode *end)
{
	if ((cur->val == SWAP * 3 && cur->prev->val == SWAP * 3 + 1)
		|| (cur->val == SWAP * 3 + 1 && cur->prev->val == SWAP * 3))
	{
		remove_node(ps->op, cur->prev);
		cur->val = SWAP * 3 + 2;
		return (cur->prev);
	}
	else if (cur->val == cur->prev->val && cur->val != SWAP * 3 + 2)
	{
		remove_node(ps->op, cur->prev);
		cur = remove_node(ps->op, cur);
		if (cur == end)
		{
			cur = cur->prev;
			ps->op->top = cur;
		}
		return (cur);
	}
	else
		return (cur->prev);
}

static t_psnode			*ps_optirot(t_ps *ps, t_psnode *cur, t_psnode *end)
{
	t_psnode	*tmp;

	tmp = cur->prev;
	while (tmp->val == cur->val && tmp != end)
		tmp = tmp->prev;
	if (cur->val % 3 == tmp->val % 3 && (cur->val / 3) + (tmp->val / 3) == 5)
	{
		remove_node(ps->op, tmp);
		cur = remove_node(ps->op, cur);
		if (cur == end)
		{
			cur = cur->prev;
			ps->op->top = cur;
		}
		return (cur);
	}
	else if ((cur->val % 3 == 0 && tmp->val == cur->val + 1)
		|| (cur->val % 3 == 1 && tmp->val == cur->val - 1))
	{
		cur->val += tmp->val % 3 + 1;
		remove_node(ps->op, tmp);
		return (cur->prev);
	}
	else
		return (tmp);
}

void					ps_opti_oplist(t_ps *ps)
{
	t_psnode	*cur;
	t_psnode	*end;
	t_optifunc	optable[4];

	optable[PUSH] = ps_optipush;
	optable[SWAP] = ps_optiswap;
	optable[ROT] = ps_optirot;
	optable[REVROT] = ps_optirot;
	cur = ps->op->top;
	while (cur != ps->op->top->next)
	{
		end = ps->op->top->next;
		if (ps->opt & F_DEBUG)
			ft_dprintf(2, "opnb : %d - opcode : %d\n", cur->idx, cur->val);
		if (!(cur = optable[cur->val / 3](ps, cur, end)))
			return ;
	}
}
