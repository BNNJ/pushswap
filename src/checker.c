/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:17:38 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:17:39 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Reads the standard input line by line,
** and executes the instruction read.
** Returns 1 if the stack is sorted after execution of the instructions,
** or 0 if it's not.
*/

static void	checker(t_ps *ps)
{
	char	*inst;

	inst = NULL;
	while ((get_next_line(0, &inst)) > 0)
	{
		if (*inst == 'p' && (inst[1] == 'a' || inst[1] == 'b') && !inst[2])
			ps_inst(ps, inst[1] - 'a', PUSH);
		else if (*inst == 's' && (inst[1] == 'a' || inst[1] == 'b') && !inst[2])
			ps_inst(ps, inst[1] - 'a', SWAP);
		else if (*inst == 's' && inst[1] == 's' && !inst[2])
			ps_inst(ps, 2, SWAP);
		else if (*inst == 'r' && (inst[1] == 'a' || inst[1] == 'b') && !inst[2])
			ps_inst(ps, inst[1] - 'a', ROT);
		else if (*inst == 'r' && inst[1] == 'r' && !inst[2])
			ps_inst(ps, 2, ROT);
		else if (*inst == 'r' && inst[1] == 'r' && !inst[3]
			&& (inst[2] == 'a' || inst[2] == 'b'))
			ps_inst(ps, inst[2] - 'a', REVROT);
		else if (*inst == 'r' && inst[1] == 'r' && inst[2] == 'r' && !inst[3])
			ps_inst(ps, 2, REVROT);
		else
			ps_exit(ps, "Error\n", EXIT_SUCCESS);
		ft_strdel(&inst);
	}
	ft_strdel(&inst);
}

static void	ps_count(t_ps *ps)
{
	t_psnode	*tmp;
	size_t		size;
	static int	count_table[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	tmp = ps->op->top;
	size = ps->op->size;
	while (size)
	{
		++count_table[tmp->val];
		tmp = tmp->prev;
		--size;
	}
	ft_printf("PA : %d\nPB : %d\n", count_table[0], count_table[1]);
	ft_printf("SA : %d\nSB : %d\nSS : %d\n",
		count_table[3], count_table[4], count_table[5]);
	ft_printf("RA : %d\nRB : %d\nRR : %d\n",
		count_table[6], count_table[7], count_table[8]);
	ft_printf("RRA : %d\nRRB : %d\nRRR : %d\n",
		count_table[9], count_table[10], count_table[11]);
	ft_printf("total : %lu instructions\n", ps->op->size);
}

static void	ps_display(t_ps *ps, int argc, char **argv)
{
	if (ps->stacks[0]->size && is_sorted(ps->stacks[0])
		&& !ps->stacks[1]->size)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	if (ps->opt & F_VIEWER)
		sdl_viewer(ps, argc, argv);
	if (ps->opt & F_DETAILS)
		ps_count(ps);
}

static inline void	ps_usage(void)
{
	ft_printf("usage:\t./checker [-d/-v] [values]\n");
	ft_printf("\t-d : details, prints extra info at the end\n");
	ft_printf("\t-v : enables viewer\n");
}

int			main(int argc, char **argv)
{
	t_ps	ps;
	t_stack	a;
	t_stack	b;
	t_stack	op;

	if (argc > 1)
	{
		ps_init(&ps, &a, &b, &op);
		ps_get_options(&ps, argv);
		if (ps.opt & F_VIEWER || ps.opt & F_DETAILS)
			ps.opt |= F_SAVE;
		if (!(parse_argv(argc, argv, &ps)))
			ps_exit(&ps, "Error\n", EXIT_FAILURE);
		if (a.size)
		{
			checker(&ps);
			ps_display(&ps, argc, argv);
		}
		ps_exit(&ps, NULL, EXIT_SUCCESS);
	}
	else
		ps_usage();
	return (EXIT_SUCCESS);
}
