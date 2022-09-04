NAME = algo_analysis

SRCS = main.c selection_sort.c bubble_sort.c insertion_sort.c heap_sort.c quick_sort.c merge_sort.c radix_sort.c
OBJS =	$(SRCS:.c=.o)
INCLUDES = -I./

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

%.o:	%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re