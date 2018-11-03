/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:37:08 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:37:09 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Reads the arguments starting with a `-` and not followed by a number,
** and compares them against a string containing possible options.
** The number of options is stored in ps->optnb.
*/

void		ps_get_options(t_ps *ps, char **argv)
{
	int		i;
	int		opt;

	i = 1;
	while (*argv[i] == '-' && (argv[i][1] < '0' || argv[i][1] > '9'))
	{
		if ((opt = ft_findchar("gvd", argv[i][1])) >= 0)
			ps->opt |= (1 << opt);
		else
			ps_exit(ps, "Error : Invalid option\n", EXIT_FAILURE);
		++i;
	}
	ps->optnb = i;
}

/*
** Some sort of ied atoi, where the computed val is added to the s.
** Whitespace are skipped in between vals, 0 is returned if a
** non digit/non whitespace character is found.
** The val to be added is checked in the process to make sure it is
** contained between INT_MIN and INT_MAX.
*/

static int	add_to_s(t_stack *s, char *str)
{
	long	v;
	char	sign;
	int		count;

	while (*str)
	{
		count = 0;
		v = 0;
		while (*str == 32 || (*str >= 9 && *str <= 13))
			++str;
		sign = *str == '+' || *str == '-' ? -(*str++ - 44) : 1;
		while (*str >= '0' && *str <= '9')
		{
			v = v * 10 + (*str++ - '0');
			++count;
		}
		if ((*str != 0 && *str != 32) || count > 10)
			return (0);
		v *= sign;
		if (v < INT_MIN || v > INT_MAX || !(add_node(s, (int)v)))
			return (0);
	}
	return (1);
}

/*
** Gets the index of each node : its final position in the sorted list,
** from 1 to the size of the list.
** Checks for duplicates in the process.
*/

static int	get_indexes(t_stack *s)
{
	t_psnode	*cur;
	t_psnode	*tmp;
	int			i;
	int			j;

	i = s->size;
	cur = s->top;
	while (i)
	{
		cur->idx = 1;
		tmp = s->top;
		j = s->size;
		while (j)
		{
			if (tmp->val < cur->val)
				++cur->idx;
			else if (tmp->val == cur->val && tmp != cur)
				return (0);
			tmp = tmp->next;
			--j;
		}
		cur = cur->next;
		--i;
	}
	return (1);
}

/*
** Outputs a s structure containining a list of vals to be sorted
** in the form of a double-linked list of slist structures.
** The vals are obtained from parsing argv or the standard input.
*/

/*
** ################# ARGV VERSION #################
*/

int			parse_argv(int argc, char **argv, t_ps *ps)
{
	t_stack	*s;
	int		i;

	s = ps->stacks[0];
	i = ps->optnb;
	while (i < argc)
	{
		if (!(add_to_s(s, argv[i])))
			return (0);
		++i;
	}
	ps->size = s->size;
	return (get_indexes(s));
}
