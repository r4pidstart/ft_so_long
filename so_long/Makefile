# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2022/09/01 23:54:47 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CFLAGS = -Wall -Wextra -Werror

LIBFT = mylibft/libft.a
LIBFT_SRCS = mylibft
SRCS = ft_draw.c ft_main.c ft_make_table.c ft_move.c ft_utils.c ft_verify_map.c

ifdef BONUS
	FOLDER = bonus/
else
	FOLDER = mandatory/
endif

all: $(NAME)

$(NAME): $(LIBFT)
	clang -Wall -Wextra -Werror -g3 -ggdb \
	-o ./so_long \
	$(addprefix $(FOLDER), $(SRCS)) \
	-Imlx -Lmlx -lmlx -framework Metal -framework Metalkit \
	-Lmylibft -lft

$(LIBFT):
	make -C $(LIBFT_SRCS) all
	
bonus:
	$(MAKE) BONUS=1 $(NAME)

clean:
	rm -rf */*.o
	make clean -C $(LIBFT_SRCS)
	
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_SRCS)

re: fclean all

.PHONY: bonus all clean fclean re