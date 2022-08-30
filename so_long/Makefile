all:
	make -C mylibft all
	clang -Wall -Wextra -Werror -g3 -ggdb \
	-o ../test \
	ft_*.c \
	-Imlx -Lmlx -lmlx -framework Metal -framework Metalkit \
	-Lmylibft -lft

clean:
	rm -r */*/*/*.o