/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:17:58 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/03 23:15:29 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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

# define TO_B 1
# define TO_A 0

# define PERCENTILE_CONSTANT 0.25
# define FIRST_QUARTER 1
# define MEDIAN 2
# define THIRD_QUARTER 3

# define ASC 0
# define DESC 1
# define SWAP 2

# define SECONDARY_OP 2
# define TERTIARY_OP 3 
typedef struct s_double_list
{
	int						element;
	int						index;
	struct s_double_list	*prev;
	struct s_double_list	*next;
}	t_double_list;

typedef struct s_chunks
{
	int		qty_elements;
	int		min;
	double	*median;
	int		max;
}	t_chunks;

typedef struct s_inner_chunks
{
	int		*qty_elements;
	double	*median;
}	t_inner_chunks;

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
	int				count_of_chunks;
	t_algo			algo;
	char			*str_id;
	t_double_list	*head_stack;
}	t_stack;

typedef struct s_operations
{
	t_list	*operations_main;
	t_list	*operations_secondary;
	t_list	*operations_tertiary;
}	t_operations;

typedef struct s_push_swap
{
	t_stack				stack_a;
	t_stack				stack_b;
	t_stack				args_list;
	t_stack				stack_aux;
	t_stack				stack_aux2;
	t_operations		operations;
	double				median;
	int					is_valid;
	int					is_sorted;
	int					argc;
	int					count_of_chunks;
	int					size;
	t_chunks			*chunks;
	char				**argv;
}	t_push_swap;

// doubly linked lists utils
int				ft_is_single_node(t_double_list *head);
int				ft_has_two_nodes(t_double_list *head);
int				ft_head_is_null(t_double_list *head);
int				ft_head_is_null(t_double_list *head);
t_double_list	*ft_find_last(t_double_list *head);
t_double_list	*ft_find_up_to_index(t_double_list *head, int max_index);
void			ft_print_all_stack(t_push_swap *push_swap);
void			ft_clear_stack(t_stack *stack);
void			ft_clear_all_stack(t_push_swap *push_swap);
void			set_min_max(t_stack *stack, int element);
void			init_min_max(t_stack *stack, int element);
int				ft_stack_is_empty(t_stack *stack);
//parse args
int				parse_args(t_push_swap *push_swap);
// operations list
void			ft_initialize_operations(t_push_swap *push_swap);
void			ft_addback_operation(t_list **operations,
					char *operation_string);
void			ft_clear_operations(t_push_swap *push_swap);
void			ft_print_operations(t_list *operations);
// operations push
void			ft_push_stack(t_stack *stack, t_double_list *new);
void			ft_pop_stack_free(t_stack *stack);
t_double_list	*ft_pop_stack_move_pointer(t_stack *stack);
int				ft_pop_push_stack_pab(t_stack *stack_first,
					t_stack *stack_second);
void			ft_print_stack(t_stack *stack);
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
int				ft_check_operation(char *operation_called, char *operation_check);
//start stack
void			ft_initialize_stack(t_stack *stack, char *str_id);
int				ft_populate_stack(t_push_swap *push_swap);
t_double_list	*ft_create_node(int element);
// call operations
void			call_single_operation(t_stack *stack, 
				t_list **operation, char *operation_start);
void			call_double_operation(t_stack *stack_first,
					t_stack *stack_second, t_list **operation,
					char *operation_start);
//sorting 
void			ft_sort(t_push_swap *push_swap);
void			ft_sort_small(t_push_swap *push_swap);
void			ft_bubble_sort(t_stack *stack_a, t_stack *stack_b,
					t_list **operations);
void			insertion_sort(t_stack *stack_a,
					t_stack *stack_b, t_list **operations);
void			ft_sort_aux_list(t_push_swap *push_swap,
					t_stack *stack, int fill_index);
int				ft_get_index(t_stack *stack, int element);
int				ft_get_ordered_index(t_stack *stack, int element);
void			ft_sort_three(t_stack *stack, t_list **operations);
void			ft_find_min_max(t_stack *stack);
int				ft_is_sorted(t_double_list *head_stack, int order);
void			ft_put_index_at_top(t_push_swap *push_swap,
					t_stack *stack, int index_ordered);
void			ft_put_element_at_top(t_push_swap *push_swap,
					t_stack *stack, int element);
double			ft_find_median(t_push_swap *push_swap, t_stack *stack,
					int fill_index);
void			ft_quick_sort_recursive(t_double_list *head,
					t_double_list *last);
void			ft_sort_aux_list(t_push_swap *push_swap,
					t_stack *stack, int fill_index);
void			ft_fill_aux_list(t_stack *stack_aux,
					t_double_list *last_a);
void			ft_less_operations_for_next_below_median(t_push_swap *push_swap,
					t_stack *stack_first, t_stack *stack_second, double median);
double			ft_find_percentile(t_push_swap *push_swap, t_stack *stack,
					int percentile);
int				ft_is_sorted_up_to_index(t_double_list *head_stack,
					int index, int order);
void			ft_clear_chunks(t_push_swap *push_swap);
void			ft_sort_aux_list_chunks(t_push_swap *push_swap, t_stack *stack,
					int elements_count);
void			ft_selection_sort_chunks_desc(t_push_swap *push_swap,
					t_stack *stack_b, t_stack *stack_a, int elements_count);
void			ft_selection_sort_chunks_asc(t_push_swap *push_swap,
					t_stack *stack_a, int elements_count);
void			ft_small_sort(t_stack *stack, t_list **operations);
void			ft_sort_three_desc(t_stack *stack, t_list **operations);
void			ft_sort_small_chunks(t_push_swap *push_swap, t_stack *stack_first,
					t_stack *stack_second);
void			ft_sort_big(t_push_swap *push_swap);
double			ft_find_percentile_chunck(t_push_swap *push_swap, t_stack *stack,
					int custom_size, double percentile_fraction);
void			ft_less_operations_for_below_index(t_push_swap *push_swap,
					t_stack *stack_first, t_stack *stack_second, int index);
void			ft_less_operations_for_above_index(t_push_swap *push_swap,
					t_stack *stack_first, t_stack *stack_second, int index);
void			ft_selection_sort_chunks_index_desc(t_push_swap *push_swap,
					int count_chunks);
void			ft_sort_big_chunks(t_push_swap *push_swap, t_stack *stack_first,
					t_stack *stack_second);
#endif //PUSH_SWAP_H