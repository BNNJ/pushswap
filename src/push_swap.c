/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:17:15 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:17:20 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Special partitioning for the first iteration, when stack B is empty.
** the partition is divided again into two sub-partitions after comparing
** the values to a sub-median. The lowest half of the partition is thus
** sent to the bottom of the stack.
*/

static inline size_t	ps_partition(t_ps *ps, size_t size)
{
	int		med;
	size_t	push_count;

	med = size / 2;
	push_count = size / 2;
	while (push_count)
	{
		if (ps->stacks[0]->top->idx <= med)
		{
			ps_inst(ps, 1, PUSH);
			--push_count;
		}
		else
			ps_inst(ps, 0, ROT);
		if (ps->stacks[1]->size > 1 && ps->stacks[1]->top->idx < med / 2)
			ps_inst(ps, 1, ROT);
	}
	return (med);
}

static void				push_swap(t_ps *ps, size_t size)
{
	size_t	part_size;

	if (ps->opt & F_DEBUG)
	{
		ft_dprintf(2, "#### INITIAL PARTITIONING ####\n");
		ft_dprintf(2, "size : %lu\n", size);
		fflush(stdout);
		read_stack(ps);
	}
	if (is_sorted(ps->stacks[0]))
		return ;
	else if (is_revsorted(ps->stacks[0]))
		ps_revsort(ps);
	else if (size <= 3)
		ps_threesort(ps, 0, size);
	else
	{
		part_size = ps_partition(ps, size);
		ps_qsort(ps, 0, size - part_size);
		ps_qsort(ps, 1, part_size);
	}
}

static inline void		ps_display(t_ps *ps, int argc, char **argv)
{
	read_oplist(ps);
	if (ps->opt & F_VIEWER)
		sdl_viewer(ps, argc, argv);
	if (ps->opt & F_DEBUG)
	{
		read_stack(ps);
		ft_dprintf(2, "sorted in %lu instructions\n", ps->op->size);
	}
}

static inline void		ps_usage(void)
{
	ft_dprintf(2, "usage:\t./push_swap [-g/-v] [values]\n");
	ft_dprintf(2, "\t-g : debug mode\n\t-v : enables viewer\n");
}

int						main(int argc, char **argv)
{
	t_ps	ps;
	t_stack	a;
	t_stack	b;
	t_stack	op;

	if (argc > 1)
	{
		ps_init(&ps, &a, &b, &op);
		ps.opt |= F_SAVE;
		ps_get_options(&ps, argv);
		if (!(parse_argv(argc, argv, &ps)))
			ps_exit(&ps, "Error\n", EXIT_FAILURE);
		push_swap(&ps, ps.stacks[0]->size);
		if (op.size)
		{
			ps_opti_oplist(&ps);
			ps_display(&ps, argc, argv);
		}
		ps_exit(&ps, NULL, EXIT_SUCCESS);
	}
	else
		ps_usage();
	return (EXIT_SUCCESS);
}
