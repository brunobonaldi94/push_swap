/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:52:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:32:59 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_send_to_b_except_three(t_push_swap *push_swap, t_stack *stack_a,
			t_stack *stack_b)
{
	int			starting_size;
	t_list		**operations;

	operations = &push_swap->operations.main;
	starting_size = stack_a->size;
	while (stack_b->size < starting_size / 2)
	{
		if (stack_a->head->index < starting_size / 2)
			ft_call_double_operation(stack_a, stack_b, operations,
				P_OP);
		else
			ft_call_single_operation(stack_a, operations, R_OP);
	}
	while (stack_a->size > 3)
		ft_call_double_operation(stack_a, stack_b, operations, P_OP);
}

void	ft_apply_best_move(t_push_swap *push_swap, t_stack *stack_a,
			t_stack *stack_b)
{
	t_list	**operations;

	operations = &push_swap->operations.main;
	ft_apply_best_move_a(stack_a, stack_b, operations);
	ft_apply_best_move_b(stack_b, operations);
	ft_call_double_operation(stack_b, stack_a, operations, P_OP);
}

void	ft_sort_smallest_moves(t_push_swap *push_swap, t_stack *stack_a,
			t_stack *stack_b)
{
	int				moves_b;
	t_double_list	*head;
	t_algo			algo;

	moves_b = 0;
	head = stack_b->head;
	stack_b->algo.moves_a = INT_MAX;
	stack_b->algo.moves_b = INT_MAX;
	while (head)
	{
		algo = ft_get_moves(stack_a, stack_b, head->index, moves_b);
		ft_save_less_moves(&stack_b->algo, algo);
		moves_b++;
		head = head->next;
	}
	ft_apply_best_move(push_swap, stack_a, stack_b);
}

void	ft_last_sort_a(t_push_swap *push_swap, t_stack *stack_a)
{
	int		min_index;
	t_list	**operations;
	char	*op;

	if (ft_is_sorted(stack_a->head, ASC) == TRUE)
		return ;
	operations = &push_swap->operations.main;
	min_index = ft_get_index(stack_a, stack_a->min);
	op = R_OP;
	if (min_index > stack_a->size / 2)
		op = RR_OP;
	while (stack_a->head->element != stack_a->min)
		ft_call_single_operation(stack_a, operations, op);
}

void	ft_sort_big(t_push_swap *push_swap)
{
	t_list	**operations;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	operations = &push_swap->operations.main;
	ft_send_to_b_except_three(push_swap, stack_a, stack_b);
	ft_small_sort(stack_a, operations);
	while (ft_stack_is_empty(stack_b) == FALSE)
		ft_sort_smallest_moves(push_swap, stack_a, stack_b);
	ft_last_sort_a(push_swap, stack_a);
}
