/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:20:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:20:07 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_psnode	*forward(t_ps *ps, t_psnode *op, t_sdl *sdl, size_t *opsize)
{
	sdl->state = 0;
	ps_inst(ps, op->val % 3, op->val / 3);
	--*opsize;
	return (op->prev);
}

static t_psnode	*backward(t_ps *ps, t_psnode *op, t_sdl *sdl, size_t *opsize)
{
	sdl->state = 0;
	++*opsize;
	op = op->next;
	ps_inst(ps, op->idx % 3, op->idx / 3);
	return (op);
}

static t_psnode	*reset(t_ps *ps, t_psnode *op, t_sdl *sdl, size_t *opsize)
{
	while (*opsize < ps->op->size)
	{
		sdl->state = 0;
		op = op->next;
		ps_inst(ps, op->idx % 3, op->idx / 3);
		++*opsize;
	}
	return (op);
}

t_psnode		*sdl_controls(t_ps *ps, t_psnode *op,
	t_sdl *sdl, size_t *opsize)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			sdl_exit(ps, sdl, EXIT_SUCCESS);
		else if (e.key.keysym.sym == SDLK_SPACE && e.key.type == SDL_KEYDOWN)
			sdl->state ^= 1;
		else if (e.key.keysym.sym == SDLK_LEFT && *opsize < ps->op->size
			&& e.key.type == SDL_KEYDOWN)
			op = backward(ps, op, sdl, opsize);
		else if (e.key.keysym.sym == SDLK_RIGHT && *opsize > 0
			&& e.key.type == SDL_KEYDOWN)
			op = forward(ps, op, sdl, opsize);
		else if (e.key.keysym.sym == SDLK_DOWN && e.key.type == SDL_KEYDOWN)
			sdl->delay += 10;
		else if (e.key.keysym.sym == SDLK_UP && e.key.type == SDL_KEYDOWN
			&& sdl->delay >= 10)
			sdl->delay -= 10;
		else if (e.key.keysym.sym == SDLK_RETURN && e.key.type == SDL_KEYDOWN)
			op = reset(ps, op, sdl, opsize);
	}
	return (op);
}
