PUSH_SWAP_CONSTANT = PUSH_SWAP
PUSH_SWAP_CONSTANT_LOWERCASE = $(echo $(PUSH_SWAP_CONSTANT) | tr A-Z a-z)

PUSH_SWAP_BONUS_CONSTANT = PUSH_SWAP
PUSH_SWAP_BONUS_CONSTANT_LOWERCASE = $(echo $(PUSH_SWAP_BONUS_CONSTANT) | tr A-Z a-z)

MAKE_C					=	make --no-print-directory
MANDATORY_PATH			=	./mandatory_srcs
BONUS_PATH				=	./bonus_srcs
PARSE_ARGS				=	./parse_args
STACK_PATH				=	./stack
OPERATIONS_PATH			=	operations
INIT_PATH				=	./init_push_swap
FREE_PATH				=	./free_push_swap
SORTING_ALGORITHM_PATH	=	sorting_algorithm
SORT_SMALL_PATH			=	$(SORTING_ALGORITHM_PATH)/sort_small
SORT_BIG_PATH			=	$(SORTING_ALGORITHM_PATH)/sort_big
SORT_UTILS_PATH			= 	$(SORTING_ALGORITHM_PATH)/sort_utils
DEBUG_PATH				=	./debug
CHECKER_PATH			=	./checker
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
		$(addprefix $(MANDATORY_PATH)/$(STACK_PATH)/, stack.c stack_utils.c stack_utils_II.c) \
		$(addprefix $(MANDATORY_PATH)/$(INIT_PATH)/, init_push_swap.c) \
		$(addprefix $(MANDATORY_PATH)/$(FREE_PATH)/, free_push_swap.c) \
		$(addprefix $(MANDATORY_PATH)/$(PARSE_ARGS)/, parse_args.c) \
		$(addprefix $(MANDATORY_PATH)/$(OPERATIONS_PATH)/, operations_push.c operations_swap.c operations_rotate_reverse.c \
															operations_list.c operations_rotate.c call_operations.c) \
		$(addprefix $(MANDATORY_PATH)/$(SORTING_ALGORITHM_PATH)/, sort.c sort_small.c sort_big.c) \
		$(addprefix $(MANDATORY_PATH)/$(SORT_UTILS_PATH)/, sort_utils.c quick_sort.c sort_aux.c sort_big_utils.c sort_small_utils.c) \
		$(addprefix $(MANDATORY_PATH)/$(DEBUG_PATH)/, debug.c)

OBJS=	$(SRCS:.c=.o)
NAME =	push_swap

SRCS_BONUS =	$(BONUS_PATH)/push_swap_bonus.c \
				$(addprefix $(BONUS_PATH)/$(STACK_PATH)/, stack_bonus.c stack_utils_bonus.c stack_utils_II_bonus.c) \
				$(addprefix $(BONUS_PATH)/$(INIT_PATH)/, init_push_swap_bonus.c) \
				$(addprefix $(BONUS_PATH)/$(FREE_PATH)/, free_push_swap_bonus.c) \
				$(addprefix $(BONUS_PATH)/$(PARSE_ARGS)/, parse_args_bonus.c) \
				$(addprefix $(BONUS_PATH)/$(OPERATIONS_PATH)/, operations_push_bonus.c operations_swap_bonus.c operations_rotate_reverse_bonus.c \
																	operations_list_bonus.c operations_rotate_bonus.c call_operations_bonus.c) \
				$(addprefix $(BONUS_PATH)/$(SORT_UTILS_PATH)/, sort_utils_bonus.c) \
				$(addprefix $(BONUS_PATH)/$(DEBUG_PATH)/, debug_bonus.c) \
				$(addprefix $(BONUS_PATH)/$(CHECKER_PATH)/, checker_bonus.c checker_bonus_utils.c)

OBJS_BONUS =	$(SRCS_BONUS:.c=.o)
NAME_BONUS =	checker

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

bonus: $(LIBFT_FULL_PATH) $(NAME_BONUS)

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

$(NAME_BONUS):	$(OBJS_BONUS) $(LIBFT_FULL_PATH)
	@tput setaf 3
	@echo COMPILING $(PUSH_SWAP_BONUS_CONSTANT)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@tput setaf 2
	@echo "$$COMPILE_DONE"
	@tput setaf 7

clean:
	@tput setaf 2
	@echo $@ libft
	@$(MAKE_C) clean -C $(SRCS_LIBFT_PATH)
	@tput setaf 4
	@echo clean $(PUSH_SWAP_CONSTANT_LOWERCASE) $(PUSH_SWAP_BONUS_CONSTANT_LOWERCASE)
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