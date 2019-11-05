# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/09 17:13:33 by dtoy              #+#    #+#              #
#    Updated: 2019/08/18 17:55:08 by ohelly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
MAKE = make
FLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -framework OpenGL -framework AppKit -lm
CFILES = \
        srcs/main.c \
		srcs/init_all.c \
		srcs/readmap.c \
		srcs/get_next_line.c \
		srcs/main_menu.c \
		srcs/key_press.c \
		srcs/play_game.c \
		srcs/output.c \
		srcs/ray_cast.c \
		srcs/find_walls.c \
		srcs/put_walls.c \
		srcs/init_pics.c \
		srcs/doors.c \
		srcs/moving.c \
		srcs/die.c
OFILES = $(CFILES:%.c=%.o)
LIBINC = libft/includes
LIBPATH = libft/
FT = ft
LFTPATH = $(LIBPATH)
LFT = $(addprefix lib, $(addsuffix .a, $(FT)))
LIBFT = -L$(LFTPATH) -l$(FT)
MKFT = $(MAKE) -C $(LFTPATH)
MLX = mlx
LMLXPATH = minilibx/
LMLX = $(addprefix lib, $(addsuffix .a, $(MLX)))
LIBMLX = -L$(LMLXPATH) -l$(MLX)
MKMLX = $(MAKE) -C $(LMLXPATH)
SRC = $(CFILES)
OBJS = $(OFILES)
INC = includes/
INCLUDES = -I$(LIBINC) -I$(LMLXPATH) -I$(INC)
LIB = -lm $(LIBFT) $(LIBMLX)
all: $(NAME)
$(NAME) : $(LFT) $(LMLX) $(OBJS)
		$(CC) -o $(NAME) $(INCLUDES) $(LIB) $(FRAMEWORKS) $(OBJS)
%.o: %.c
		$(CC) $(FLAGS) -o $@ $(INCLUDES) -c $<
$(LFT):
		$(MKFT)
$(LMLX):
		$(MKMLX)
clean:
		$(MKFT) clean
		$(MKMLX) clean
		rm -rf $(OBJS)
fclean: clean
		$(MKFT) fclean
		rm -rf $(NAME)
re: fclean all
