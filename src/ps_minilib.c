/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_minilib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:23:20 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:23:21 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_free_stack(t_stack *s)
{
	t_psnode	*tmp;

	while (s->size)
		if ((tmp = ft_pop(s)))
			free(tmp);
}

void	read_stack(t_ps *ps)
{
	t_psnode	*tmp;
	size_t		i;

	i = ps->stacks[0]->size;
	tmp = ps->stacks[0]->top;
	ft_printf("STACK A :  ");
	while (i)
	{
		ft_printf("%d, ", tmp->idx);
		tmp = tmp->prev;
		--i;
	}
	ft_printf("\n");
	i = ps->stacks[1]->size;
	tmp = ps->stacks[1]->top;
	ft_printf("STACK B :  ");
	while (i)
	{
		ft_printf("%d, ", tmp->idx);
		tmp = tmp->prev;
		--i;
	}
	ft_printf("\n");
}

/*
** Checks if a stack is sorted in ascending order
*/

int		is_sorted(t_stack *s)
{
	t_psnode	*tmp;

	tmp = s->top;
	while (tmp != s->top->next)
	{
		if (tmp->val > tmp->prev->val)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}

/*
** Checks if a stack is sorted in descending order
*/

int		is_revsorted(t_stack *s)
{
	t_psnode	*tmp;

	tmp = s->top;
	while (tmp != s->top->next)
	{
		if (tmp->val < tmp->prev->val)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}
