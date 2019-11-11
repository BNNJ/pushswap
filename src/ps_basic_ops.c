/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_basic_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:19:46 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:19:46 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** creates a node and add it to the end of a stack
*/

int			add_node(t_stack *s, int v)
{
	t_psnode	*tmp;

	if (!(tmp = (t_psnode*)malloc(sizeof(t_psnode))))
		return (0);
	tmp->val = v;
	ft_pushback(s, tmp);
	return (1);
}

/*
** Removes and destroys a node from a stack.
** The node isn't necessarily on top of the stack, contrary to ft_pop.
*/

t_psnode	*remove_node(t_stack *s, t_psnode *node)
{
	t_psnode	*tmp;

	if (s->size >= 1)
	{
		tmp = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
		--s->size;
		return (tmp);
	}
	else if (s->size == 1)
	{
		free(node);
		s->top = NULL;
		s->size = 0;
		return (NULL);
	}
	else
		return (NULL);
}

/*
** Removes the top element of a stack and returns it
*/

t_psnode	*ft_pop(t_stack *s)
{
	t_psnode	*ret;

	if (!s->top)
		return (NULL);
	else if (s->size == 1)
	{
		ret = s->top;
		s->top = NULL;
	}
	else
	{
		ret = s->top;
		s->top = s->top->prev;
		s->top->next = ret->next;
		s->top->next->prev = ret->prev;
	}
	--s->size;
	return (ret);
}

/*
** Adds an element to the top of a stack
*/

void		ft_push(t_stack *s, t_psnode *new)
{
	if (new)
	{
		if (s->top)
		{
			new->next = s->top->next;
			new->prev = s->top;
			new->prev->next = new;
			new->next->prev = new;
			s->top = new;
		}
		else
		{
			s->top = new;
			s->top->next = new;
			s->top->prev = new;
		}
		++s->size;
	}
}

/*
** Adds an element to the end of a stack
*/

void		ft_pushback(t_stack *s, t_psnode *new)
{
	if (new)
	{
		if (s->top)
		{
			new->next = s->top->next;
			new->prev = s->top;
			new->prev->next = new;
			new->next->prev = new;
		}
		else
		{
			s->top = new;
			s->top->next = new;
			s->top->prev = new;
		}
		++s->size;
	}
}
