/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_viewer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:12:24 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 13:12:25 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		sdl_exit(t_ps *ps, t_sdl *sdl, uint8_t status)
{
	if (status == EXIT_FAILURE)
		ft_printf("SDL Error : %s\n", SDL_GetError());
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	if (sdl->rend)
		SDL_DestroyRenderer(sdl->rend);
	SDL_Quit();
	ps_exit(ps, NULL, status);
}

/*
** Resets the stacks and options, runs the oplist through ps_revert_op which
** sets the idx member of each node to the opposite instruction stored in val.
** Then initializes everything needed by SDL.
*/

static void	sdl_init(t_ps *ps, t_sdl *sdl, int argc, char **argv)
{
	ps->opt = 0;
	*sdl = (t_sdl){NULL, NULL, NULL, 0, 0};
	ps_free_stack(ps->stacks[0]);
	ps_free_stack(ps->stacks[1]);
	ps_revert_op(ps->op);
	if (!(parse_argv(argc, argv, ps)))
		ps_exit(ps, NULL, EXIT_FAILURE);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		sdl_exit(ps, sdl, EXIT_FAILURE);
	if (!(sdl->win = SDL_CreateWindow("Push Swap", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		sdl_exit(ps, sdl, EXIT_FAILURE);
	if (!(sdl->rend = SDL_CreateRenderer(sdl->win, -1,
		SDL_RENDERER_ACCELERATED)))
		sdl_exit(ps, sdl, EXIT_FAILURE);
	if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 25))
		sdl_exit(ps, sdl, EXIT_FAILURE);
	SDL_RenderClear(sdl->rend);
}

static void	sdl_draw_stack(t_ps *ps, uint8_t s, t_sdl *sdl)
{
	t_psnode	*tmp;
	SDL_Rect	rect;
	size_t		stack_size;

	if (ps->stacks[s]->size)
	{
		tmp = ps->stacks[s]->top->next;
		stack_size = ps->stacks[s]->size;
		rect.h = (HEIGHT - 100) / ps->size;
		rect.y = HEIGHT - 50 - rect.h;
		while (stack_size)
		{
			rect.w = tmp->idx * ((WIDTH - 150) / (2 * ps->size));
			rect.x = s ? 50 + (WIDTH / 2) : (WIDTH / 2) - 50 - rect.w;
			if (SDL_SetRenderDrawColor(sdl->rend, 255,
				255 - (tmp->idx * 255 / ps->size), 25, 255) != 0)
				sdl_exit(ps, sdl, EXIT_FAILURE);
			if (SDL_RenderFillRect(sdl->rend, &rect) != 0)
				sdl_exit(ps, sdl, EXIT_FAILURE);
			rect.y -= rect.h;
			tmp = tmp->next;
			--stack_size;
		}
	}
}

static void	sdl_draw(t_ps *ps, t_sdl *sdl)
{
	if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 25) != 0)
		sdl_exit(ps, sdl, EXIT_FAILURE);
	SDL_RenderClear(sdl->rend);
	if (SDL_SetRenderDrawColor(sdl->rend, 255, 25, 25, 255) != 0)
		sdl_exit(ps, sdl, EXIT_FAILURE);
	sdl_draw_stack(ps, 0, sdl);
	sdl_draw_stack(ps, 1, sdl);
	SDL_RenderPresent(sdl->rend);
}

void		sdl_viewer(t_ps *ps, int argc, char **argv)
{
	t_sdl		sdl;
	t_psnode	*op;
	size_t		op_size;

	sdl_init(ps, &sdl, argc, argv);
	op = ps->op->top;
	op_size = ps->op->size;
	while (42)
	{
		sdl_draw(ps, &sdl);
		op = sdl_controls(ps, op, &sdl, &op_size);
		if (op_size && sdl.state)
		{
			ps_inst(ps, op->val % 3, op->val / 3);
			op = op->prev;
			--op_size;
			SDL_Delay(sdl.delay);
		}
	}
	sdl_exit(ps, &sdl, EXIT_SUCCESS);
}
