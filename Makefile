# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 15:04:58 by ysakahar          #+#    #+#              #
#    Updated: 2023/02/21 12:31:38 by ysakahar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall
MLXF	= -L /usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
FSANIA	= -fsanitize=address
FSANIL	= -fsanitize=leak

MLX_DIR		= minilibx-linux/
MLX_NAME	= libmlx_Darwin.a
MLX			= $(MLX_DIR)$(MLX_NAME)

LIBFT_DIR	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_DIR)$(LIBFT_NAME)

INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

SRC_DIR	=	src/
SRC			=	main.c \
				initialization.c \
				utils.c \
				events.c \
				render.c \
				color.c \
				parse_args.c \
				help_msg.c \
				fractal_sets/mandelbrot.c \
				fractal_sets/julia.c \
				fractal_sets/burning_ship.c \
				fractal_sets/tricorn.c \
				fractal_sets/mandelbox.c \
				color_schemes/color_interpolated.c \
				color_schemes/color_special.c \
				color_schemes/color_striped.c \

SRCS		= $(addprefix $(SRC_DIR), $(SRC))

# Objects
OBJ_DIR	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ))

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(OBJS): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)fractal_sets/
	@mkdir $(OBJ_DIR)color_schemes/

$(MLX):
	@echo "Making MiniLibX..."
	make -sC $(MLX_DIR)

$(LIBFT):
	@echo "Making libft..."
	make -sC $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "Compiling fractol..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(INC) $(MLXF) $(MLX)
	@echo "Fractol ready."

bonus: all

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	@echo ".o object files Removed."

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)$(LIBFT_NAME)
	@echo "fractol Removed."

re: fclean all

.PHONY: all bonus clean fclean re