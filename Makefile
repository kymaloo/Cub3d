
NAME	:= cub3D

CFLAGS	:= -Wextra -Wall -Werror -g3

HEADERS	:= -Iinclude

SRCS	:= 	\
			memory_manager/mm_area.c					\
			memory_manager/mm_elem.c					\
			memory_manager/mm.c							\
			memory_manager/utils/mm_utils.c				\
			memory_manager/utils/mm_bitfield_utils.c	\
			memory_manager/utils/mm_destruction_utils.c	\
			memory_manager/utils/mm_hashmap_utils.c		\
			src/main.c									\
			src/error.c									\
			src/parsing/open_close_map.c				\
			src/parsing/init_direction_and_fc.c			\
			src/parsing/stock_direction_and_fc.c		\
			src/parsing/check_map.c						\
			src/parsing/init.c							\
			src/parsing/free.c							\
			src/parsing/path_finding.c					\
			src/parsing/stock_map.c						\
			src/parsing/utils_parse.c					\
			src/parsing/colors_fc.c						\


OBJS	:= ${SRCS:.c=.o}

LIBFT	:= ./libft
LIBFT_EXE := ./libft/libft.a

all: $(NAME)

n:
	norminette

r:
	make re && ./cub3D maps/map.cub

v:
	make re && valgrind --leak-check=full -s --track-origins=yes ./cub3D maps/map.cub

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "\033[34m----Compiling ${NAME}---\033[0m"
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) -lm $(OBJS) $(LIBFT_EXE) $(HEADERS) -o $(NAME)
	@echo "\033[32m----${NAME} Compiled!----\033[0m"
	
clean:
	@echo "\033[31m----Cleaning object files----\033[0m"
	@rm -rf $(OBJS)
	@$(MAKE) clean -C  $(LIBFT)

fclean: clean
	@echo "\033[31m----Cleaning all generated files----\033[0m"
	@rm -rf $(NAME)
	@$(MAKE) fclean -C  $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re