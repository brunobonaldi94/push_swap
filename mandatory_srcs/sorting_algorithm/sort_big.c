/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:52:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 19:54:20 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_send_to_b_except_three(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int			starting_size;
	t_list	**operations;
	
	operations = &push_swap->operations.operations_main;
	starting_size = stack_first->size;
	while (stack_second->size < starting_size / 2)
	{
		if (stack_first->head_stack->index < starting_size / 2)
			call_double_operation(stack_first, stack_second, operations, P_OP);
		else
			call_single_operation(stack_first, operations, R_OP);
	}
	while (stack_first->size > 3)
		call_double_operation(stack_first, stack_second, operations, P_OP);
}

int		ft_find_position(t_stack *stack, int element_index)
{
	t_double_list	*head;
	int				pos;
	int				current_index;
	int				past_index;

	head = stack->head_stack;
	current_index = 0;
	past_index  = INT_MAX;
	while (head)
	{
		if (head->index > element_index && head->index < past_index)
		{
			pos = current_index;
			past_index = head->index;
		}
		current_index++;
		head = head->next;
	}
	if (past_index != INT_MAX)
		return (pos);
	return (ft_get_index(stack, stack->max) + 1);
}

t_algo	ft_get_moves(t_stack *stack_a, t_stack *stack_b, int element_index,
		int current_pos)
{
	int				moves_a;
	t_algo			algo;

	moves_a = ft_find_position(stack_a, element_index);
	if (moves_a > stack_a->size / 2)
		moves_a = moves_a - stack_a->size;
	if (current_pos > stack_b->size / 2)
		current_pos = current_pos - stack_b->size;
	algo.moves_a = moves_a;
	algo.moves_b = current_pos;
	return (algo);
}

void	ft_save_less_moves(t_algo *algo, t_algo new_algo)
{
	long int	algo_one_sum;
	long int	algo_two_sum;

	algo_one_sum = ft_abs_number(algo->moves_a) 
		+ ft_abs_number(algo->moves_b);
	algo_two_sum = ft_abs_number(new_algo.moves_a) 
		+ ft_abs_number(new_algo.moves_b);
	if (algo_one_sum > algo_two_sum)
	{
		algo->moves_a = new_algo.moves_a;
		algo->moves_b = new_algo.moves_b;
	}
}

void	ft_apply_best_move(t_push_swap *push_swap, 
			t_stack *stack_a, t_stack *stack_b)
{
	t_list	**operations;

	operations = &push_swap->operations.operations_main;
	while (stack_b->algo.moves_a != 0)
	{
		if (stack_b->algo.moves_a < 0 && stack_b->algo.moves_b < 0)
		{
			call_double_operation(stack_a, stack_b, operations, RR_OP);
			stack_b->algo.moves_a++;
			stack_b->algo.moves_b++;
		}
		else if (stack_b->algo.moves_a > 0 && stack_b->algo.moves_b > 0)
		{
			call_double_operation(stack_a, stack_b, operations, R_OP);
			stack_b->algo.moves_a--;
			stack_b->algo.moves_b--;
		}
		if (stack_b->algo.moves_a < 0)
		{
			call_single_operation(stack_a, operations, RR_OP);
			stack_b->algo.moves_a++;
		}
		else if (stack_b->algo.moves_a > 0)
		{
			call_single_operation(stack_a, operations, R_OP);
			stack_b->algo.moves_a--;
		}		
	}
	while (stack_b->algo.moves_b != 0)
	{
		if (stack_b->algo.moves_b < 0)
		{
			call_single_operation(stack_b, operations, RR_OP);
			stack_b->algo.moves_b++;
		}
		else
		{
			call_single_operation(stack_b, operations, R_OP);
			stack_b->algo.moves_b--;
		}
	}
	call_double_operation(stack_b, stack_a, operations, P_OP);
}

void	ft_sort_smallest_moves(t_push_swap *push_swap,
			t_stack *stack_a, t_stack *stack_b) 
{
	int				moves_b;
	t_double_list	*head;
	t_algo			algo;
	
	moves_b = 0;
	head = stack_b->head_stack;
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

	if (ft_is_sorted(stack_a->head_stack, ASC) == TRUE)
		return ;
	operations = &push_swap->operations.operations_main;
 	min_index = ft_get_index(stack_a, stack_a->min);
	op = R_OP;
	if (min_index > stack_a->size / 2)
		op = RR_OP;
	while (stack_a->head_stack->element != stack_a->min)
		call_single_operation(stack_a, operations, op);
 }

void	ft_sort_big(t_push_swap *push_swap)
{
	t_list	**operations;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	operations = &push_swap->operations.operations_main;
	ft_send_to_b_except_three(push_swap, stack_a, stack_b);
	ft_small_sort(stack_a, operations);
	while (ft_stack_is_empty(stack_b) == FALSE)
		ft_sort_smallest_moves(push_swap, stack_a, stack_b);
	ft_last_sort_a(push_swap, stack_a);
}