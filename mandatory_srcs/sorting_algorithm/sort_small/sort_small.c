/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:35:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/21 23:25:36 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack *stack, t_list **operations);
void	ft_sort_two(t_stack *stack, t_list **operations);

int	return_min_order(int desc, int asc)
{
	if (desc < asc)
		return (DESC);
	return (ASC);
}

int	ft_simulate_a_to_b(t_stack *stack_a, t_stack *stack_b)
{
	t_double_list	*last;
	t_double_list	*head;
	int				index[2];

	last = ft_find_last(stack_b->head_stack);
	index[0] = 0;
	head = stack_b->head_stack;
	while (stack_a->head_stack->element < head->element)
	{
		index[ASC]++;
		head = head->next;
	}
	head = stack_b->head_stack;
	index[1] = 0;
	while (stack_a->head_stack->element < head->element)
	{
		if (index[DESC]++ == 0)
		{
			head = last;
			continue ;
		}
		head = last->prev;
	}
	return (return_min_order(index[DESC], index[ASC]));
}

int	ft_simulate_b_to_a(t_stack *stack_a, t_stack *stack_b)
{
	t_double_list	*last;
	t_double_list	*head;
	int				index[2];

	last = ft_find_last(stack_a->head_stack);
	index[0] = 0;
	head = stack_a->head_stack;
	if (ft_head_is_null(head) || ft_head_is_null(stack_b->head_stack))
		return (2);
	while (stack_b->head_stack->element > head->element)
	{
		index[ASC]++;
		head = head->next;
	}
	head = stack_a->head_stack;
	index[1] = 0;
	while (stack_b->head_stack->element > head->element)
	{
		if (index[DESC]++ == 0)
		{
			head = last;
			continue ;
		}
		head = last->prev;
	}
	return (return_min_order(index[DESC], index[ASC]));
}

int	ft_simulate_shortest_path(t_stack *stack_first, t_stack *stack_second)
{
	if (stack_first->str_id[0] == STACK_A[0])
		return (ft_simulate_b_to_a(stack_first, stack_second));
	return (ft_simulate_a_to_b(stack_second, stack_first));
}

char	*ft_set_operation(int diff, int size, double half, int order)
{
	char	*op;

	if (diff == size - 1)
	{
		op = R_OP;
		if (order == DESC)
			op = RR_OP;
	}
	else if (diff <= half)
		op = R_OP;
	else
		op = RR_OP;
	return (op);
}

int	ft_set_moves(int diff, int size, double half)
{
	int	moves;

	if (diff == size - 1)
		moves = 1;
	else if (diff <= half)
		moves = diff;
	else
		moves = size - diff;
	return(moves);
}

t_op_moves	ft_pick_smallest_rotate(t_stack *stack, int element, int index_to)
{
	t_op_moves	op_moves;
	int			index_from[2];
	int			diff;
	double		half;

	op_moves.moves = 0;
	index_from[0] = ft_get_index(stack, element);
	half = (double)stack->size / 2.0;
	index_from[1] = ASC;
	if (index_from[0] <= index_to)
		diff = index_to - index_from[0];
	else
	{
		index_from[1] = DESC;
		diff = index_from[0] - index_to;
	}
	op_moves.op = P_OP;
	if (diff == 0)
		return (op_moves);
	op_moves.op = ft_set_operation(diff, stack->size, half, index_from[1]);
	op_moves.moves = ft_set_moves(diff, stack->size, half);
	return (op_moves);
}

void	ft_sort_five(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	t_list	**operations;
	int		order;

	operations = &push_swap->operations.operations_main;
	while (stack_second->size < 2)
		call_double_operation(stack_first, stack_second, &push_swap->operations.operations_main,P_OP);
	ft_sort_three(stack_first, operations);
	ft_sort_two(stack_second, operations);
	while (stack_second->size != 0)
	{
		if (stack_second->head_stack->element < stack_first->head_stack->next->element)
		{
			call_double_operation(stack_second, stack_first, operations, P_OP);
			ft_sort_two(stack_first, operations);
		}
		else
		{
			order = ft_simulate_shortest_path(stack_first, stack_second);
			if (order == ASC)
			{
				while (stack_second->head_stack->element > stack_first->head_stack->next->element)
					call_single_operation(stack_first, operations, R_OP);
			}
			else
			{
				while (stack_second->head_stack->element > stack_first->head_stack->next->element)
					call_single_operation(stack_first, operations, RR_OP);
			}				
		}
	}
	stack_first->op_moves = ft_pick_smallest_rotate(stack_first, stack_first->min, 0);
	while (stack_first->op_moves.moves)
	{
		call_single_operation(stack_first, operations, stack_first->op_moves.op);
		stack_first->op_moves.moves--;
	}
}


void	ft_sort_small_chunks(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
		t_list	**operations;
		int		index_min;
		int		index_max;
		int		starting_size;

		operations = &push_swap->operations.operations_main;
		starting_size = stack_first->size;
		index_min = ft_get_index(stack_first, -1);
		index_max = ft_get_index(stack_first, stack_first->max);
		ft_sort_aux_list(push_swap, &push_swap->stack_a, TRUE);
		if (index_min == 1)
			call_single_operation(stack_first, operations, S_OP);
		else if (index_min == starting_size - 1)
			call_single_operation(stack_first, operations, RR_OP);
		if (index_max == 0)
			call_single_operation(stack_first, operations, R_OP);
		while (stack_second->size != starting_size / 2)
		{
			call_double_operation(stack_first, stack_second, operations, P_OP);
			ft_sort_two(stack_second, operations);
		}
		while (stack_second->size)
		{
			if (ft_calculate_less_amount_moves(push_swap, stack_second, stack_first) == SECONDARY_OP)
				ft_apply_calculated_moves(push_swap, stack_first, stack_second, 
				push_swap->operations.operations_secondary);
			else
				ft_apply_calculated_moves(push_swap, stack_first, stack_second,
				push_swap->operations.operations_tertiary);
		}
		stack_first->op_moves = ft_pick_smallest_rotate(stack_first,
			stack_first->min, 0);
		while (stack_first->op_moves.moves)
		{
			call_single_operation(stack_first, operations, stack_first->op_moves.op);
			stack_first->op_moves.moves--;
		}
}

void	ft_sort_four(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{

	t_list	**operations;
	char	*last_operation;
	int		index;
	int		index_min;
	int		index_max;

	operations = &push_swap->operations.operations_main;
	index_min = ft_get_index(stack_first, stack_first->min);
	index_max = ft_get_index(stack_first, stack_first->max);
	if (index_min == 1)
	{
		call_single_operation(stack_first, operations, S_OP);
		if (ft_is_sorted(stack_first, ASC) == TRUE)
			return ;
	}
	else if (index_min == 3 || (index_max == 3 && index_min != 1))
	{
		call_single_operation(stack_first, operations, RR_OP);
		if (ft_is_sorted(stack_first, ASC) == TRUE)
			return ;
	}
	else if (index_min == 1 || index_max == 1)
	{
		call_single_operation(stack_first, operations, S_OP);
		if (ft_is_sorted(stack_first, ASC) == TRUE)
			return ;
	}
	call_double_operation(stack_first, stack_second, operations, P_OP);
	ft_sort_three(stack_first, operations);
	if (stack_second->head_stack->element == push_swap->global_max)
	{
		call_double_operation(stack_first, stack_second, operations, P_OP);
		call_single_operation(stack_first, operations, R_OP);
		return ;
	}
	if (ft_simulate_shortest_path(stack_first, stack_second) == ASC)
		last_operation = R_OP;
	else
		last_operation = RR_OP;
	while (stack_second->head_stack->element > stack_first->head_stack->element)
		call_single_operation(stack_first, operations,
			last_operation);
	call_double_operation(stack_second, stack_first, operations, P_OP);
	if (stack_first->str_id[0] == STACK_A[0])
		index = ft_get_index(stack_first, push_swap->global_min);
	else
		index = ft_get_index(stack_first, push_swap->global_max);
	if (index > stack_first->size / 2)
	{
		last_operation = RR_OP;
		index = stack_first->size - index;
	}
	else
		last_operation = R_OP;
	while (index != 0)
	{
		call_single_operation(stack_first, operations, last_operation);
		index--;
	}
}

void	ft_sort_three(t_stack *stack, t_list **operations)
{
	int	element_head;
	int	element_next;

	element_head = stack->head_stack->element;
	element_next = stack->head_stack->next->element;
	if (element_head == stack->min && element_next == stack->max)
	{
		call_single_operation(stack, operations, RR_OP);
		call_single_operation(stack, operations, S_OP);
	}
	else if (element_head != stack->max && element_next == stack->min)
		call_single_operation(stack, operations, S_OP);
	else if (element_head != stack->min && element_next == stack->max)
		call_single_operation(stack, operations, RR_OP);
	else if (element_head == stack->max && element_next == stack->min)
		call_single_operation(stack, operations, R_OP);
	else if (element_head == stack->max && element_next != stack->min)
	{
		call_single_operation(stack, operations, R_OP);
		call_single_operation(stack, operations, S_OP);
	}
}

void	ft_sort_two(t_stack *stack, t_list **operations)
{
	if (ft_head_is_null(stack->head_stack)
		|| ft_is_single_node(stack->head_stack))
		return ;
	if (stack->str_id[0] == STACK_B[0])
	{
		if (stack->head_stack->element < stack->head_stack->next->element)
			call_single_operation(stack, operations, S_OP);
		return ;
	}
	if (stack->head_stack->element > stack->head_stack->next->element)
			call_single_operation(stack, operations, S_OP);

}


void	ft_set_stacks(t_push_swap *push_swap, t_stack	**stack_first,
			t_stack **stack_second, char *a_or_b)
{
	if (a_or_b[0] == STACK_A[0])
	{
		(*stack_first) = &push_swap->stack_a;
		(*stack_second) = &push_swap->stack_b;
	}
	else
	{
		(*stack_first) = &push_swap->stack_b;
		(*stack_second) = &push_swap->stack_a;
	}
}

void	ft_sort_small(t_push_swap *push_swap, char *a_or_b)
{
	t_stack	*stack_first;
	t_stack	*stack_second;

	ft_set_stacks(push_swap, &stack_first, &stack_second, a_or_b);
	if (push_swap->stack_a.size == 1)
		return ;
	else if (push_swap->stack_a.size == 2)
		ft_sort_two(stack_first, &push_swap->operations.operations_main);
	else if (push_swap->stack_a.size == 3)
		ft_sort_three(stack_first, &push_swap->operations.operations_main);
	else if (push_swap->stack_a.size == 4)
		ft_sort_four(push_swap, stack_first, stack_second);
	else
		ft_sort_small_chunks(push_swap, stack_first, stack_second);
}