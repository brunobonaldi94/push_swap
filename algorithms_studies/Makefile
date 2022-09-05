MAKE_C					=	make --no-print-directory
NAME = algo_analysis

SRCS = main.c selection_sort.c bubble_sort.c insertion_sort.c heap_sort.c quick_sort.c merge_sort.c radix_sort.c quick_sort_interative.c
OBJS =	$(SRCS:.c=.o)

SRCS_LIBFT_PATH = ./../libs/libft/
LIBFT = libft.a
LIBFT_FULL_PATH = $(addprefix $(SRCS_LIBFT_PATH), $(LIBFT))

INCLUDES = -I./ -I$(SRCS_LIBFT_PATH)includes -I$(SRCS_LIBFT_PATH) 

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

%.o:	%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(LIBFT_FULL_PATH) $(NAME)

$(LIBFT_FULL_PATH):
	@tput setaf 4
	@echo COMPILING LIBFT
	@$(MAKE_C) bonus -C $(SRCS_LIBFT_PATH)
	@cp $(LIBFT_FULL_PATH) ./

$(NAME):	$(OBJS) $(LIBFT_FULL_PATH)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re