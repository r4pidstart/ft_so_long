# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2022/09/04 20:18:43 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CFLAGS = -Wall -Wextra -Werror

LIBFT = mylibft/libft.a
LIBFT_SRCS = mylibft
MANDATORY_SRCS = ft_draw.c ft_main.c ft_make_table.c ft_move.c ft_utils.c ft_verify_map.c
BONUS_SRCS = ft_draw_bonus.c ft_main_bonus.c ft_make_table_bonus.c ft_move_bonus.c ft_utils_bonus.c ft_verify_map_bonus.c

ifdef BONUS
	FOLDER = bonus_src/
	SRCS = $(BONUS_SRCS)
else
	FOLDER = mandatory_src/
	SRCS = $(MANDATORY_SRCS)
endif

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(FOLDER), $(SRCS:.c=.o))
	clang -Wall -Wextra -Werror -g3 -ggdb \
	-o ./so_long \
	$(addprefix $(FOLDER), $(SRCS)) \
	-Imlx -Lmlx -lmlx -framework OpenGL -framework Appkit \
	-Lmylibft -lft

$(LIBFT):
	make -C $(LIBFT_SRCS) all

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@
	
bonus:
	$(MAKE) BONUS=1 $(NAME)

clean:
	rm -rf */*.o
	make clean -C $(LIBFT_SRCS)
	
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_SRCS)

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re