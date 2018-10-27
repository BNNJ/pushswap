CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g

SRC_DIR		=	./src

SRC			=	$(addprefix $(SRC_DIR)/,$(SRCS))

SRCS		=	checker.c			\
				push_swap.c			\
				ps_parser.c			\
				ps_init_exit.		\
				ps_basic_ops.c		\
				ps_instructions.c	\
				ps_oplist.c			\
				ps_quicksort.c		\
				ps_minisort.c		\
				ps_opti.c			\
				ps_viewer.c			\
				ps_controls.c		\
				ps_viewertext.c		\
				ps_minilib.c

OBJ_DIR		=	./obj

OBJ_PS		=	$(addprefix $(OBJ_DIR)/,$(OBJS_PS))
OBJ_CH		=	$(addprefix $(OBJ_DIR)/,$(OBJS_CH))

OBJS_PS		=	push_swap.o			\
				ps_parser.o			\
				ps_init_exit.o		\
				ps_basic_ops.o		\
				ps_instructions.o	\
				ps_oplist.o			\
				ps_minilib.o		\
				ps_quicksort.o		\
				ps_minisort.o		\
				ps_opti.o			\
				ps_viewer.o			\
				ps_controls.o		\
				ps_viewertext.o

OBJS_CH		=	checker.o			\
				ps_parser.o			\
				ps_init_exit.o		\
				ps_basic_ops.o		\
				ps_instructions.o	\
				ps_oplist.o			\
				ps_minilib.o		\
				ps_viewer.o			\
				ps_controls.o		\
				ps_viewertext.o

INC_DIR		=	./include
INC			=	$(INC_DIR)/push_swap.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBFT_INC	=	$(LIBFT_DIR)/includes

FTPF_DIR	=	./ft_printf
FTPF		=	$(FTPF_DIR)/libftprintf.a
FTPF_INC	=	$(FTPF_DIR)/include

SDL_DIR		=	./sdl2
SDL			=	$(SDL_DIR)/lib/libSDL2.a
TTF			=	$(SDL_DIR)/lib/libSDL2_ttf.a
SDL_INC		=	$(SDL_DIR)/include/SDL2

INC_FLAGS	=	-I$(INC_DIR) -I$(LIBFT_INC) -I$(SDL_INC) -I$(FTPF_INC)
LINK_FLAGS	=	-L$(LIBFT_DIR) -lft -L$(SDL_DIR)/lib -lSDL2 -lSDL2_ttf	\
				-L$(FTPF_DIR) -lftprintf

all:			push_swap checker

push_swap:		$(OBJ_DIR) $(OBJ_PS) $(LIBFT) $(FTPF) message_ps
	@$(CC) $(CFLAGS) -o push_swap $(OBJ_PS) $(INC_FLAGS) $(LINK_FLAGS)

checker:		$(OBJ_DIR) $(OBJ_CH) $(LIBFT) $(FTPF) message_ch
	@$(CC) $(CFLAGS) -o checker $(OBJ_CH) $(INC_FLAGS) $(LINK_FLAGS)

message_ch:
	@echo compiling checker...

message_ps:
	@echo compiling push_swap...

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(FTPF):
	@make -C $(FTPF_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(FTPF_DIR) clean
	@echo cleaning objects...
	@rm -rf $(OBJ_DIR)

fclean:
	@make clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FTPF_DIR) fclean
	@echo cleaning binaries...
	@rm -f push_swap checker

re:
	@make fclean
	@make all

.PHONY:			all clean fclean re
