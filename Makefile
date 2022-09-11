PUSH_SWAP_CONSTANT = PUSH_SWAP
PUSH_SWAP_CONSTANT_LOWERCASE = $(echo $(PUSH_SWAP_CONSTANT) | tr A-Z a-z)

MAKE_C					=	make --no-print-directory
MANDATORY_PATH			=	./mandatory_srcs
PARSE_ARGS				=	./parse_args
DOUBLY_LINKED_LIST_PATH	=	doubly_linked_list
OPERATIONS_PATH			=	operations
SORTING_ALGORITHM_PATH	=	sorting_algorithm

define COMPILE_DONE

  _____  _    _  _____ _    _    _______          __     _____             _____   ____  _   _ ______ 
 |  __ \| |  | |/ ____| |  | |  / ____\ \        / /\   |  __ \           |  __ \ / __ \| \ | |  ____|
 | |__) | |  | | (___ | |__| | | (___  \ \  /\  / /  \  | |__) |  ______  | |  | | |  | |  \| | |__   
 |  ___/| |  | |\___ \|  __  |  \___ \  \ \/  \/ / /\ \ |  ___/  |______| | |  | | |  | | . ` |  __|  
 | |    | |__| |____) | |  | |  ____) |  \  /\  / ____ \| |               | |__| | |__| | |\  | |____ 
 |_|     \____/|_____/|_|  |_| |_____/    \/  \/_/    \_\_|               |_____/ \____/|_| \_|______|

endef
export COMPILE_DONE

SRCS =	$(MANDATORY_PATH)/push_swap.c \
		$(addprefix $(MANDATORY_PATH)/$(DOUBLY_LINKED_LIST_PATH)/, doubly_linked_list.c doubly_linked_list_utils.c doubly_linked_list_utils_II.c) \
		$(addprefix $(MANDATORY_PATH)/$(PARSE_ARGS)/, parse_args.c) \
		$(addprefix $(MANDATORY_PATH)/$(OPERATIONS_PATH)/, operations_push.c operations_swap.c operations_rotate_reverse.c operations_rotate.c call_operations.c) \
		$(addprefix $(MANDATORY_PATH)/$(SORTING_ALGORITHM_PATH)/, sort.c quick_sort.c)

OBJS =	$(SRCS:.c=.o)
NAME =	push_swap

SRCS_LIBFT_PATH = ./libs/libft/
LIBFT = libft.a
LIBFT_FULL_PATH = $(addprefix $(SRCS_LIBFT_PATH), $(LIBFT))

INCLUDES = -I$(SRCS_LIBFT_PATH)includes -I$(SRCS_LIBFT_PATH) -I./includes

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

NORMINETTE_PATHS = $(shell find . -maxdepth 1 ! -path . -type d ! -path '*algorithms_studies*' -type d ! -path '*git*' | tr '\n' ' ')

%.o:	%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(LIBFT_FULL_PATH) $(NAME)

$(LIBFT_FULL_PATH):
	@tput setaf 4
	@echo COMPILING LIBFT
	@$(MAKE_C) bonus -C $(SRCS_LIBFT_PATH)
	@cp $(LIBFT_FULL_PATH) ./

$(NAME):	$(OBJS) $(LIBFT_FULL_PATH)
	@tput setaf 3
	@echo COMPILING $(PUSH_SWAP_CONSTANT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@tput setaf 2
	@echo "$$COMPILE_DONE"
	@tput setaf 7

clean:
	@tput setaf 2
	@echo $@ libft
	@$(MAKE_C) clean -C $(SRCS_LIBFT_PATH)
	@tput setaf 4
	@echo clean $(PUSH_SWAP_CONSTANT_LOWERCASE)
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@tput setaf 7

fclean:	clean
	@tput setaf 3
	@echo $@
	@$(MAKE_C) fclean -C $(SRCS_LIBFT_PATH)
	@$(RM) $(NAME) $(NAME_BONUS) $(LIBFT)
	@tput setaf 7

norm:
	norminette $(NORMINETTE_PATHS) | grep -v OK

re:	fclean all

.PHONY:	all clean fclean re bonus