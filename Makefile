# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 15:04:58 by ysakahar          #+#    #+#              #
#    Updated: 2023/02/26 19:41:25 by ysakahar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol
CC			= gcc
CFLAGS		= -Werror -Wextra -Wall
MLXF		= -L /usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
FSANIA		= -fsanitize=address
FSANIL		= -fsanitize=leak

MLX_DIR		= minilibx-linux/
MLX_NAME	= libmlx_Darwin.a
MLX			= $(MLX_DIR)$(MLX_NAME)

LIBFT_DIR	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_DIR)$(LIBFT_NAME)

INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

SRC_DIR		=	src/
SRC			=	main.c \
				initialization.c \
				args_parser.c \
				color.c \
				render_fractal.c \
				events.c \
				display_help.c \
				clean_exit.c \
				fractal_formulas/mandelbrot.c \
				fractal_formulas/julia.c \
				fractal_formulas/burning_ship.c \
				fractal_formulas/tricorn.c \
				fractal_formulas/mandelbox.c \
				fractal_formulas/multibrot.c \
				color_functions/interpolate.c \
				color_functions/stripe.c \
				color_functions/special.c \

SRCS		= $(addprefix $(SRC_DIR), $(SRC))
OBJ_DIR		= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ))

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(OBJS): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)fractal_formulas/
	@mkdir $(OBJ_DIR)color_functions/

$(MLX):
	@echo "Compiling MiniLibX..."
	make -sC $(MLX_DIR)

$(LIBFT):
	@echo "Compiling libft..."
	make -sC $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "Compiling fractol..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(INC) $(MLXF) $(MLX)
	@echo "Fractol compiled successfully."

bonus: all

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	@echo "Object files removed."

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)$(LIBFT_NAME)
	@echo "Fractol binary removed."

re: fclean all

.PHONY: all bonus clean fclean re