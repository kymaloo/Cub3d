NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

BRED	:=	\033[1;31m
YELLOW	:=	\033[33m
GREEN	:=	\033[32m
BLUE	:=	\033[1;34m
RESET	:=	\033[0m

SRC =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
	 	ft_isalpha.c \
	 	ft_isascii.c \
	 	ft_isdigit.c \
	 	ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
	 	ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
	 	ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
	 	ft_strlcpy.c \
	 	ft_strlen.c \
		ft_strmapi.c \
	 	ft_strncmp.c \
		ft_strnstr.c \
	 	ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
	 	ft_tolower.c \
	 	ft_toupper.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstsize_bonus.c \
		get_next_line.c \
		strncmp_with_array.c \
		strjoin_gnl.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@printf "$(BLUE)$(NAME): compiling objects:\n$(BLUE)$(NAME): compiling $(RESET)%-33.33s\033[F" $@
	@$(CC) $(CFLAGS) -o $@ -c $< || (echo "$(BLUE)$(NAME): $(BRED) $< Compilation failure$(RESET)" && return 1)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@printf "\33[2K\r$(BLUE)$(NAME): objects $(GREEN)compiled$(RESET)\n"
	@printf "\33[2K\r$(BLUE)$(NAME): $(NAME) $(GREEN)archived$(RESET)\n"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re