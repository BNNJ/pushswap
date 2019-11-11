/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:21:47 by pfragnou          #+#    #+#             */
/*   Updated: 2019/04/16 20:21:48 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_CALC_H
# define RPN_CALC_H

# define T_VAL	0
# define T_OP	1

typedef int					(*t_rpnfunc)(int, int, int*);

typedef struct s_rpn_node	t_rpn_node;

struct						s_rpn_node{
	int			type;
	int			val;
	t_rpn_node	*next;
	t_rpn_node	*prev;
};

typedef struct				s_rpn_stack
{
	t_rpn_node	*top;
	t_rpn_node	*bot;
	int			size;
}							t_rpn_stack;

int							rpn_calc(t_rpn_stack *s, int *ret);
void						push(t_rpn_stack *s, t_rpn_node *op);
void						push_back(t_rpn_stack *s, t_rpn_node *op);
t_rpn_node					*pop(t_rpn_stack *s);
int							pop_f(t_rpn_stack *s);
t_rpn_node					*new_node(int type, int val);

int							op_add(int b, int a, int *ret);
int							op_sub(int b, int a, int *ret);
int							op_mul(int b, int a, int *ret);
int							op_div(int b, int a, int *ret);
int							op_mod(int b, int a, int *ret);

#endif
