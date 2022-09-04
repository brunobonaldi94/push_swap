/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:17:58 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/04 21:16:10 by bbonaldi         ###   ########.fr       */
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

typedef	struct s_double_list
{
	int						element;
	struct s_double_list*	prev;
	struct s_double_list*	next;
}	t_double_list;

typedef struct s_stack
{
	int				size;
	t_double_list	*head_stack;
}	t_stack;

typedef	struct s_push_swap
{
	t_stack		stack_a;
	t_stack		stack_b;
	int			argc;
	char		**argv;
}	t_push_swap;

// doubly linked lists utils
int				ft_has_no_head(t_double_list **head);
int				ft_is_single_node(t_double_list **head);
int				ft_has_two_nodes(t_double_list **head);
int				ft_head_is_null(t_double_list **head);
int				ft_check_head_nulish(t_double_list **head);
t_double_list	*ft_find_last(t_double_list *head);
void			ft_print_all_stack(t_push_swap *push_swap);
void			ft_clear_all_stack(t_push_swap *push_swap);
// operations push
void			ft_push_stack(t_double_list **head, t_double_list *new,
					int *size);
void			ft_pop_stack_free(t_double_list **head, int *size);
t_double_list	*ft_pop_stack_move_pointer(t_double_list **head, int *size);
void			ft_pop_push_stack_pab(t_double_list **head_first,
					t_double_list **head_second, int *size_first,
					int *size_second);
// operations swap		
void			ft_swap_stack_sab(t_double_list **head);
void			ft_swap_stack_ss(t_double_list **head_a,
					t_double_list **head_b);
// operations rotate reverse
void			ft_rotate_stack_rrab(t_double_list **head);
void			ft_rotate_stack_rrr(t_double_list **head_a,
					t_double_list **head_b);
// operations rotate
void			ft_rotate_stack_rab(t_double_list **head);
void			ft_rotate_stack_rr(t_double_list **head_a,
					t_double_list **head_b);
//start stack
void			ft_initialize_stack(t_stack *stack);
void			ft_populate_stack(t_push_swap *push_swap);
t_double_list	*ft_create_node(int element);
//sorting 
void			ft_sort(t_push_swap *push_swap);
void			ft_quick_sort(t_push_swap *push_swap);
#endif //PUSH_SWAP_H