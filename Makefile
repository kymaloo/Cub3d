
NAME		:= cub3D
LIBFT_DIR	:= ./libft
MLX_DIR		:= ./MLX42
LIBFT_A		:= $(LIBFT_DIR)/libft.a
MLX_A		:= $(MLX_DIR)/build/libmlx42.a

#got that hash from `git submodule status`. we're using it for versionning of the MLX42 purposes.
MLX_VERSION_GIT_HASH := ce254c3a19af8176787601a2ac3490100a5c4c61

INCLUDES	:= -Iinclude -IMLX42/include
ARCHIVES	:= $(LIBFT_A) $(MLX_A)
LIBS		:= -ldl -lglfw -lm
CFLAGS		:= -Wextra -Wall -Werror -g3 $(INCLUDES)

RED		:=	\033[31m
YELLOW	:=	\033[33m
GREEN	:=	\033[32m
BLUE	:=	\033[34m
RESET	:=	\033[0m

ERROR	= 0;

SRCS	:= 	\
			memory_manager/mm_area.c					\
			memory_manager/mm_elem.c					\
			memory_manager/mm.c							\
			memory_manager/utils/mm_utils.c				\
			memory_manager/utils/mm_bitfield_utils.c	\
			memory_manager/utils/mm_destruction_utils.c	\
			memory_manager/utils/mm_hashmap_utils.c		\
			memory_manager/safe_allocations.c			\
			\
			src/main.c									\
			src/error.c									\
			\
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

all: clear $(MLX_A) $(LIBFT_A) $(NAME) 

n:	clear
	norminette

r:	re
	./cub3D maps/map.cub

v:	re
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./cub3D maps/map.cub

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< || (echo "$(BLUE)$(NAME): $(RED) $< Compilation failure$(RESET)" && return 1)

$(LIBFT_A): $(LIBFT_DIR)
	@echo "$(BLUE)$(NAME): archiving $(LIBFT_A)$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(BLUE)$(NAME): $(GREEN)$(LIBFT_A) archived !$(RESET)"

$(LIBFT_DIR):
	git submodule update --init --recursive $(LIBFT_DIR)

$(MLX_A): $(MLX_DIR)
	@echo "$(BLUE)$(NAME): archiving $(MLX_A)$(RESET)"
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4
	@echo "$(BLUE)$(NAME): $(GREEN)$(MLX_A) archived !$(RESET)"

$(MLX_DIR):
	@echo "$(BLUE)$(NAME): $(YELLOW)$(MLX_DIR) missing$(RESET)"
	@echo "$(BLUE)$(NAME): cloning missing git $(MLX_DIR) submodule$(RESET)"
	git submodule update --init --recursive $(MLX_DIR)
	@echo "$(BLUE)$(NAME): setting $(MLX_DIR) submodule to ce254c3 for versionning$(RESET)"
	cd $(MLX_DIR) && git checkout $(MLX_VERSION_GIT_HASH) && cd ..


$(NAME): $(OBJS)
	@echo "$(BLUE)$(NAME): Compiling $$(OBJS) ${NAME}$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(ARCHIVES) -o $(NAME)
	@echo "$(BLUE)$(NAME): $(GREEN)${NAME} Compiled!$(RESET)"

clear:
	clear

clean:
	@echo "$(BLUE)$(NAME): Cleaning object files$(RESET)"
	@rm -rf $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(BLUE)$(NAME): Cleaning $(NAME)$(RESET)"
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: clear fclean all

.PHONY: all, clean, fclean, re, n, r, v, clear