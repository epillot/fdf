# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epillot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/04 16:40:08 by epillot           #+#    #+#              #
#    Updated: 2017/02/17 17:12:41 by epillot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAG = -Wall -Wextra -Werror

SRC_NAME =  get_map.c\
			main.c\
			draw_segment.c\

SRC_PATH = srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj/

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INC = ./includes/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@make -C minilibx/
	@echo "\033[35mmaking $(NAME)...\033[0m"
	@gcc $(FLAG) -o $(NAME) $(OBJ) -I $(INC) -L ./libft/ -lft -L ./minilibx/ -lmlx -framework OpenGL -framework AppKit
	@echo "\033[32mdone\033[0m"
	
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p obj
	@gcc $(FLAG) -c -I $(INC) $< -o $@

clean:
	@make fclean -C libft/
	@make clean -C minilibx/
	@/bin/rm -f
	@echo "\033[34mobj \033[32mcleaned\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[34m$(NAME) \033[32mremoved\033[0m"

re: fclean all
