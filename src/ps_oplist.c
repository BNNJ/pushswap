/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_oplist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:34:15 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:34:16 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static inline void	ps_putopstr(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	write(1, str, len);
	write(1, "\n", 1);
}

void				read_oplist(t_ps *ps)
{
	t_psnode	*tmp;
	int			i;
	static char	*opstr[12] = {
		[0] = "pa",
		[1] = "pb",
		[3] = "sa",
		[4] = "sb",
		[5] = "ss",
		[6] = "ra",
		[7] = "rb",
		[8] = "rr",
		[9] = "rra",
		[10] = "rrb",
		[11] = "rrr"
	};

	tmp = ps->op->top;
	i = ps->op->size;
	while (i)
	{
		ps_putopstr(opstr[tmp->val]);
		tmp = tmp->prev;
		--i;
	}
}

void				ps_revert_op(t_stack *op)
{
	size_t		size;
	t_psnode	*tmp;
	int			table[12];

	table[0] = 1;
	table[1] = 0;
	table[3] = 3;
	table[4] = 4;
	table[5] = 5;
	table[6] = 9;
	table[7] = 10;
	table[8] = 11;
	table[9] = 6;
	table[10] = 7;
	table[11] = 8;
	size = op->size;
	tmp = op->top;
	while (size)
	{
		tmp->idx = table[tmp->val];
		tmp = tmp->prev;
		--size;
	}
}
