/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:12:54 by pfragnou          #+#    #+#             */
/*   Updated: 2018/10/26 12:12:58 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*
** Instructions codes
** To be used as an argument to the instruction wrapper ps_inst
*/

# define PUSH 0
# define SWAP 1
# define ROT 2
# define REVROT 3

/*
** option flags
*/

# define F_DEBUG 1
# define F_VIEWER 2
# define F_DETAILS 4
# define F_SAVE 64

/*
** Viewer window size constants
*/

# define WIDTH 1920
# define HEIGHT 1040

# include "ft_printf.h"
# include "libft.h"
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

/*
** The basic node element.
** val : the value stored in the node
** idx : The linearized value, or in other words its final place
** 		in the sorted list. Makes finding medians and sorting much easier.
**
** For disgusting reasons, this structure has also been reused to build
** the instructions list, in which case :
** val : the instruction
** idx : The opposite instruction, ie the instruction to apply
** 		to reverse the instruction stored in val.
*/

typedef struct	s_psnode
{
	int				val;
	int				idx;
	struct s_psnode	*prev;
	struct s_psnode	*next;
}				t_psnode;

/*
** Stacks are represented as a circular doubly linked list, to make
** rotation instructions easier.
*/

typedef struct	s_stack
{
	t_psnode		*top;
	size_t			size;
}				t_stack;

typedef struct	s_ps
{
	int				opt;
	int				optnb;
	t_stack			*stacks[2];
	t_stack			*op;
	size_t			size;
}				t_ps;

typedef void		(*t_inst)(t_ps*, uint8_t);
typedef t_psnode*	(*t_optifunc)(t_ps*, t_psnode*, t_psnode*);

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	TTF_Font		*font;
	uint32_t		delay;
	uint8_t			state;
}				t_sdl;

/*
** ps_parser.c
*/

void begin (void) __attribute__((constructor));
void end (void) __attribute__((destructor));

int				parse_argv(int argc, char **argv, t_ps *ps);
void			ps_get_options(t_ps *ps, char **argv);

/*
** ps_quicksort.c && ps_minisort.c
*/

void			ps_qsort(t_ps *ps, uint8_t s, size_t size);
void			ps_minisort(t_ps *ps, uint8_t s, size_t size);
void			ps_threesort(t_ps *ps, uint8_t s, size_t size);
void			ps_revsort(t_ps *ps);

/*
** ps_instructions.c
*/

void			ps_inst(t_ps *ps, uint8_t s, int instcode);

/*
** ps_basic_ops.c
*/

int				add_node(t_stack *s, int v);
t_psnode		*remove_node(t_stack *s, t_psnode *nod);
t_psnode		*ft_pop(t_stack *s);
void			ft_push(t_stack *s, t_psnode *new);
void			ft_pushback(t_stack *s, t_psnode *new);

/*
** ps_oplist.c
*/

void			read_oplist(t_ps *ps);
void			ps_revert_op(t_stack *op);

/*
** ps_opti.c
*/

void			ps_opti_oplist(t_ps *ps);

/*
** ps_viewer.c && ps_controls.c && ps_viewertext.c
*/

void			sdl_viewer(t_ps *ps, int argc, char **argv);
t_psnode		*sdl_controls(t_ps *ps, t_psnode *op, t_sdl *sdl,
	size_t *opsize);
void			sdl_exit(t_ps *ps, t_sdl *sdl, uint8_t status);
void			ps_draw_controls(t_ps *ps, t_sdl *sdl);
void			ps_draw_op(t_ps *ps, t_sdl *sdl, t_psnode *op, size_t size);

/*
** ps_init_exit.c
*/

void			ps_init(t_ps *ps, t_stack *a, t_stack *b, t_stack *op);
void			ps_exit(t_ps *ps, char *exit_msg, int exit_status);

/*
** minilib.c
*/

void			ps_free_stack(t_stack *s);
int				is_sorted(t_stack *s);
int				is_revsorted(t_stack *s);
void			read_stack(t_ps *ps);

#endif
