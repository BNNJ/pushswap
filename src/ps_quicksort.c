/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:09:48 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 13:09:49 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Helper function to get the median of a list of values
*/

static inline int		ps_get_median(t_ps *ps, uint8_t s, size_t size)
{
	int			min;
	int			max;
	t_psnode	*tmp;

	min = INT_MAX;
	max = 0;
	tmp = ps->stacks[s]->top;
	while (size)
	{
		if (tmp->idx < min)
			min = tmp->idx;
		if (tmp->idx > max)
			max = tmp->idx;
		tmp = tmp->prev;
		--size;
	}
	return ((min + max - 1) / 2);
}

/*
** ##### QUICKSORT #####
** Partitions a stack and pushes the partition to the other stack,
** until the partition is small enough that it can be sorted with
** another sorting algorithm.
*/

static inline size_t	ps_split(t_ps *ps, uint8_t s, size_t part_size, int med)
{
	int		rot_count;

	rot_count = 0;
	while (part_size)
	{
		if (s ? ps->stacks[s]->top->idx > med : ps->stacks[s]->top->idx <= med)
		{
			ps_inst(ps, s ^ 1, PUSH);
			--part_size;
		}
		else
		{
			ps_inst(ps, s, ROT);
			++rot_count;
		}
	}
	return (rot_count);
}

static inline size_t	ps_partition(t_ps *ps, uint8_t s, size_t size)
{
	int		med;
	size_t	rot_count;
	size_t	part_size;

	med = ps_get_median(ps, s, size);
	part_size = s ? (size + 1) / 2 : size / 2;
	size -= part_size;
	rot_count = ps_split(ps, s, part_size, med);
	if (size != ps->stacks[s]->size)
		while (rot_count--)
			ps_inst(ps, s, REVROT);
	return (part_size);
}

void					ps_qsort(t_ps *ps, uint8_t s, size_t size)
{
	size_t	part_size;

	if (size <= 3)
	{
		if (ps->opt & F_DEBUG)
		{
			ft_printf("#### MINISORT STACK %c ####\n", s + 'A');
			ft_printf("size : %lu\n", size);
			read_stack(ps);
		}
		ps_minisort(ps, s, size);
	}
	else
	{
		if (ps->opt & F_DEBUG)
		{
			ft_printf("#### QUICKSORT STACK %c ####\n", s + 'A');
			ft_printf("size : %lu\n", size);
			read_stack(ps);
		}
		part_size = ps_partition(ps, s, size);
		ps_qsort(ps, 0, s ? part_size : size - part_size);
		ps_qsort(ps, 1, s ? size - part_size : part_size);
	}
}
