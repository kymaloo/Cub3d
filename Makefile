
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
CFLAGS		:= -Wall -Wextra -Werror -g3 $(INCLUDES)

BRED	:=	\033[1;31m
RED		:=	\033[31m
YELLOW	:=	\033[33m
GREEN	:=	\033[32m
BLUE	:=	\033[1;34m
RESET	:=	\033[0m

SRCS	:= 	\
			memory_manager/mm_area.c					\
			memory_manager/mm_elem.c					\
			memory_manager/mm.c							\
			memory_manager/utils/mm_utils.c				\
			memory_manager/utils/mm_bitfield_utils.c	\
			memory_manager/utils/mm_destruction_utils.c	\
			memory_manager/utils/mm_hashmap_utils.c		\
			memory_manager/safe_allocations.c			\
			memory_manager/safe_allocations2.c			\
			memory_manager/user_functions.c				\
			\
			src/main.c									\
			src/init_utils.c							\
			src/init_utils2.c							\
			src/error.c									\
			\
			src/parsing/open_close_map.c				\
			src/parsing/check_line_map.c				\
			src/parsing/init_direction_and_fc.c			\
			src/parsing/stock_direction_and_fc.c		\
			src/parsing/check_map.c						\
			src/parsing/init.c							\
			src/parsing/path_finding.c					\
			src/parsing/stock_map.c						\
			src/parsing/utils_parse.c					\
			src/parsing/colors_fc.c						\
			src/parsing/parsing_utils.c					\
			\
			src/exec/minimap.c		\
			src/exec/dda.c			\
			src/exec/dda_utils.c	\
			src/exec/draw_wall.c	\
			src/exec/raycast.c		\
			\
			src/hooks/keys_hook.c						\
			src/hooks/loop_hook.c						\
			src/hooks/mouse_hooks.c						\
			src/hooks/player_move_translations.c		\
			src/hooks/utils.c							\
			\
			src/debug/debug_main.c						\
			src/debug/debug_parsing.c					\
			src/debug/debug_utils.c						\
			src/debug/debug_utils2.c					\
			\



OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

n:	clear
	norminette src include libft memory_manager

a:	clear all
	./cub3D maps/map.cub

l:	clear all
	lldb ./cub3D maps/map.cub

r:	clear re
	./cub3D maps/map.cub

v:	clear all
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes --track-fds=yes ./cub3D maps/map.cub

vs:	clear all
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes --suppressions=.valgrind.supp ./cub3D maps/map.cub

%.o: %.c
	@printf "$(BLUE)$(NAME): compiling objects:\n$(BLUE)$(NAME): compiling $(RESET)%-45.45s\n" $@
#@printf "$(BLUE)$(NAME): compiling objects:\n$(BLUE)$(NAME): compiling $(RESET)%-33.33s\033[F" $@
	@$(CC) $(CFLAGS) -o $@ -c $< && printf "\033[F\033[F" || (echo "$(BLUE)$(NAME): $(BRED) $<: error: $(RESET)compilation failure$(RESET)" && return 1)

$(LIBFT_A):
	@echo "$(BLUE)$(NAME): archiving $(LIBFT_A)$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(BLUE)$(NAME): $(GREEN)$(LIBFT_A) archived !$(RESET)"

#creates the MLX_A using cmake if it's missing
$(MLX_A): $(MLX_DIR)
	@echo "$(BLUE)$(NAME): versionning $(MLX_DIR) submodule$(RESET)"
	@git submodule update --init --recursive $(MLX_DIR)
	@echo "$(BLUE)$(NAME): setting $(MLX_DIR) submodule to ce254c3$(RESET)"
	@cd $(MLX_DIR) && git checkout $(MLX_VERSION_GIT_HASH) && cd ..
	@echo "$(BLUE)$(NAME): archiving $(MLX_A)$(RESET)"
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4
	@echo "$(BLUE)$(NAME): $(GREEN)$(MLX_A) archived !$(RESET)"

#git clones the MLX_DIR if it's missing
$(MLX_DIR):
	@echo "$(BLUE)$(NAME): $(YELLOW)$(MLX_DIR) missing$(RESET)"
	@echo "$(BLUE)$(NAME): cloning missing git $(MLX_DIR) submodule$(RESET)"
	@git submodule update --init --recursive $(MLX_DIR)

#checks dependencies left to right
$(NAME): $(MLX_A) $(LIBFT_A) $(OBJS) 
	@printf "\33[2K\r$(BLUE)$(NAME): objects $(GREEN)compiled$(RESET)\n"
	@echo "$(CC) $(CFLAGS) \$$($(NAME)_OBJS) $(ARCHIVES) $(LIBS) -o $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(ARCHIVES) $(LIBS) -o $(NAME)

	@printf "\33[2K\r$(BLUE)$(NAME): $(NAME) $(GREEN)Linked!$(RESET)\n"

compile_without_mlx: $(LIBFT_A) $(OBJS)
	@echo "$(BLUE)$(NAME): objects $(GREEN)compiled !$(RESET)"
	@echo "$(BLUE)$(NAME): Linking $(NAME) $(RESET)"
	@echo "$(CC) $(CFLAGS) $(OBJS) $(ARCHIVES) $(LIBS) -o $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(ARCHIVES) $(LIBS) -o $(NAME)
	@echo "$(BLUE)$(NAME): $(GREEN)$(NAME) Linked without mlx !$(RESET)"

clear:
	@clear

clean:
	@echo "$(BLUE)$(NAME): Cleaning object files$(RESET)"
	@rm -rf $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(BLUE)$(NAME): Cleaning $(NAME)$(RESET)"
	@rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	
fclean_mlx: fclean
	@echo "$(BLUE)$(NAME): Fcleaning $(MLX_DIR)$(RESET)"
	@rm -rf $(MLX_DIR)

gprof: clear $(LIBFT_A) $(OBJS)
	@echo "$(BLUE)$(NAME): $(NAME) $(GREEN)OBJS compiled !$(RESET)"
	@echo "$(BLUE)$(NAME): Linking $(NAME) with -gp $(RESET)"
	@echo "$(CC) $(CFLAGS) -gp $(OBJS) $(ARCHIVES) $(LIBS) -o $(NAME)"
	@$(CC) $(CFLAGS) -gp $(OBJS) $(ARCHIVES) $(LIBS) -o $(NAME)
	@echo "$(BLUE)$(NAME): $(GREEN)$(NAME) Linked !$(RESET)"
	./$(NAME) ./maps/map.cub && gprof $(NAME) gmon.out > analysis.txt && cat analysis.txt

re: clear fclean all

re_project_only: clear
	@echo "$(BLUE)$(NAME): Cleaning object files$(RESET)"
	@rm -rf $(OBJS)
	@echo "$(BLUE)$(NAME): Cleaning $(NAME)$(RESET)"
	@rm -rf $(NAME)
	make all

re_mlx: clear fclean_mlx all

.PHONY: all, clean, fclean, re, n, v, clear, compile_without_mlx, gprof, fclean_mlx, re_mlx