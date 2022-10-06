/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:17:58 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 00:45:23 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include <unistd.h>
# include "libft.h"
# include "stdlib.h"

# define TRUE 1
# define FALSE 0

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"

# define ERROR_CODE 1
# define SUCCESS_CODE 0
# define ERROR_CODE_FUNCTION -1

# define MAX_OPERATION_LEN 2

# define STACK_A "a"
# define STACK_B "b"
# define STACK_AUX "x"
# define STACK_ARGS "g"

# define SA "sa"
# define SB "sb"
# define SS "ss"
# define PA "pa"
# define PB "pb"
# define RA "ra"
# define RB "rb"
# define RR "rr"
# define RRA "rra"
# define RRB "rrb"
# define RRR "rrr"

# define S_OP "s"
# define P_OP "p"
# define R_OP "r"
# define RR_OP "rr"

# define ASC 0
# define DESC 1

# define ERROR "Error\n"
# define OK "OK"
# define KO "KO"

typedef struct s_double_list
{
	int						element;
	int						index;
	struct s_double_list	*prev;
	struct s_double_list	*next;
}	t_double_list;

typedef struct s_algo
{
	long int	moves_a;
	long int	moves_b;
}	t_algo;

typedef struct s_stack
{
	int				size;
	int				min;
	int				max;
	t_algo			algo;
	char			*str_id;
	t_double_list	*head;
}	t_stack;

typedef struct s_operations
{
	t_list	*main;
	t_list	*checker;
}	t_operations;

typedef struct s_push_swap
{
	t_stack				stack_a;
	t_stack				stack_b;
	t_stack				args_list;
	t_stack				stack_aux;
	t_operations		operations;
	int					is_valid;
	int					is_sorted;
	int					argc;
	char				**argv;
}	t_push_swap;

//init
void			ft_initialize_operations(t_push_swap *push_swap);
void			t_initialize_stack(t_stack *stack, char *str_id);
int				ft_initialize_push_swap(t_push_swap *push_swap, int argc,
					char *argv[]);
void			ft_load_argc_argv(t_push_swap *push_swap, int argc,
					char *argv[]);
//clear
void			ft_clear_stack(t_stack *stack);
void			ft_clear_all_stack(t_push_swap *push_swap);
void			ft_clear_operations(t_push_swap *push_swap);
int				ft_print_error(t_push_swap *push_swap);
void			ft_clear_push_swap(t_push_swap *push_swap);
// stack utils
int				ft_is_single_node(t_double_list *head);
int				ft_has_two_nodes(t_double_list *head);
int				ft_head_is_null(t_double_list *head);
t_double_list	*ft_find_last(t_double_list *head);
void			ft_print_stack(t_stack *stack);
void			ft_print_all_stack(t_push_swap *push_swap);
void			ft_set_min_max(t_stack *stack, int element);
int				ft_stack_is_empty(t_stack *stack);
//parse args
int				ft_parse_args(t_push_swap *push_swap);
// operations list
void			ft_initialize_operations(t_push_swap *push_swap);
void			ft_addback_operation(t_list **operations,
					char *operation_string);
void			ft_print_operations(t_list *operations);
// operations push
void			ft_push_stack(t_stack *stack, t_double_list *new);
void			ft_pop_stack_free(t_stack *stack);
t_double_list	*ft_pop_stack_move_pointer(t_stack *stack);
int				ft_pop_push_stack_pab(t_stack *stack_first,
					t_stack *stack_second);
// operations swap
void			ft_swap_stack(t_stack *stack);
int				ft_swap_stack_sab(t_stack *stack);
int				ft_swap_stack_ss(t_stack *stack_a, t_stack *stack_b);
// operations rotate reverse
int				ft_rotate_stack_rrab(t_stack *stack);
int				ft_rotate_stack_rrr(t_stack *stack_a, t_stack *stack_b);
// operations rotate
int				ft_rotate_stack_rab(t_stack *stack);
int				ft_rotate_stack_rr(t_stack *stack_a, t_stack *stack_b);
// operations utils
int				ft_check_operation(char *operation_called,
					char *operation_check);
//start stack
void			ft_initialize_stack(t_stack *stack, char *str_id);
int				ft_populate_stack(t_push_swap *push_swap);
t_double_list	*ft_create_node(int element);
// call operations
void			ft_call_single_operation(t_stack *stack,
					t_list **operation, char *op);
void			ft_call_double_operation(t_stack *stack_first,
					t_stack *stack_second, t_list **operation,
					char *op);
//sorting 
void			ft_sort(t_push_swap *push_swap);
void			ft_sort_small(t_push_swap *push_swap);
void			ft_sort_aux_list(t_push_swap *push_swap,
					t_stack *stack, int fill_index);
int				ft_get_index(t_stack *stack, int element);
void			ft_sort_two(t_stack *stack, t_list **operations);
void			ft_sort_three(t_stack *stack, t_list **operations);
void			ft_find_min_max(t_stack *stack);
int				ft_is_sorted(t_double_list *head_stack, int order);
void			ft_put_element_at_top(t_push_swap *push_swap,
					t_stack *stack, int element);
void			ft_quick_sort_recursive(t_double_list *head,
					t_double_list *last);
void			ft_fill_aux_list(t_stack *stack_aux,
					t_double_list *last_a);
void			ft_small_sort(t_stack *stack, t_list **operations);
void			ft_sort_three_desc(t_stack *stack, t_list **operations);
void			ft_sort_big(t_push_swap *push_swap);
int				ft_find_position(t_stack *stack, int element_index);
t_algo			ft_get_moves(t_stack *stack_a, t_stack *stack_b,
					int element_index, int current_pos);
void			ft_save_less_moves(t_algo *algo, t_algo new_algo);
void			ft_apply_best_move_b(t_stack *stack_b, t_list **operations);
void			ft_apply_best_move_a(t_stack *stack_a, t_stack *stack_b,
					t_list	**operations);
//checker
void			ft_checker_bonus(t_push_swap *push_swap);
void			ft_print_result(int is_sorted);
#endif //PUSH_SWAP_BONUS_H