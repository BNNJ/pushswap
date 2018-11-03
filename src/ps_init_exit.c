/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_init_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:04:33 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 13:04:34 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_exit(t_ps *ps, char *exit_msg, int exit_status)
{
	size_t	len;

	if (exit_msg)
	{
		len = 0;
		while (exit_msg[len])
			++len;
		write(exit_status == EXIT_SUCCESS ? 1 : 2, exit_msg, len);
	}
	if (ps->stacks[0]->size)
		ps_free_stack(ps->stacks[0]);
	if (ps->stacks[1]->size)
		ps_free_stack(ps->stacks[1]);
	if (ps->op->size)
		ps_free_stack(ps->op);
	exit(exit_status);
}

void	ps_init(t_ps *ps, t_stack *a, t_stack *b, t_stack *op)
{
	*a = (t_stack){NULL, 0};
	*b = (t_stack){NULL, 0};
	*op = (t_stack){NULL, 0};
	ps->stacks[0] = a;
	ps->stacks[1] = b;
	ps->op = op;
	ps->opt = 0;
}
