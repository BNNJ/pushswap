/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_viewertext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:38:27 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 19:38:29 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static const char	*g_opstr[12] = {
	[0] = "pa",
	[1] = "pb",
	[3] = "sa",
	[4] = "sb",
	[5] = "ss",
	[6] = "ra",
	[7] = "rb",
	[8] = "rr",
	[9] = "rra",
	[10] = "rrb",
	[11] = "rrr"
};

static inline void	ps_draw_text(t_ps *ps, t_sdl *sdl,
	const char *txt, t_point *pos)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	color;
	SDL_Rect	rect;

	color = (SDL_Color){255, 255, 255, 255};
	if (!(surface = (TTF_RenderText_Solid(sdl->font, txt, color))))
		sdl_exit(ps, sdl, EXIT_FAILURE);
	if (!(texture = SDL_CreateTextureFromSurface(sdl->rend, surface)))
	{
		SDL_FreeSurface(surface);
		sdl_exit(ps, sdl, EXIT_FAILURE);
	}
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x = pos->x;
	rect.y = pos->y;
	SDL_RenderCopy(sdl->rend, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void				ps_draw_op(t_ps *ps, t_sdl *sdl, t_psnode *op, size_t size)
{
	t_point	pos;

	pos.y = 20;
	pos.x = 500;
	ps_draw_text(ps, sdl, "previous instruction :", &pos);
	pos.x = 1000;
	if (size != ps->op->size)
		ps_draw_text(ps, sdl, g_opstr[op->next->val], &pos);
	pos.x = 1300;
	ps_draw_text(ps, sdl, "next instruction :", &pos);
	pos.x = 1700;
	if (size)
		ps_draw_text(ps, sdl, g_opstr[op->val], &pos);
}

void				ps_draw_controls(t_ps *ps, t_sdl *sdl)
{
	t_point	pos;

	pos.y = HEIGHT - 60;
	pos.x = 300;
	ps_draw_text(ps, sdl, "start/pause : space", &pos);
	pos.x = 900;
	ps_draw_text(ps, sdl, "previous/next step : left/right", &pos);
	pos.x = 1700;
	ps_draw_text(ps, sdl, "faster/slower : up/down", &pos);
}
