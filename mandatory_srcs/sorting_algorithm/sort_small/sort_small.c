/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:35:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/18 23:26:46 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack *stack, t_list **operations);


void	ft_sort_five(t_push_swap *push_swap)
{
	return (void)(push_swap);
}

int	return_min_order(int desc, int asc)
{
	if (desc < asc)
		return (DESC);
	return (ASC);
}

int	ft_simulate_a_to_b(t_stack *stack_a, t_stack *stack_b)
{
	t_double_list	*last;
	t_double_list	*head_b;
	int				index[2];

	last = ft_find_last(stack_b->head_stack);
	index[0] = 0;
	head_b = stack_b->head_stack;
	while (stack_a->head_stack->element < head_b->element)
	{
		index[ASC]++;
		head_b = head_b->next;
	}
	head_b = stack_a->head_stack;
	index[1] = 0;
	while (stack_b->head_stack->element < head_b->element)
	{
		if (index[DESC]++ == 0)
		{
			head_b = last;
			continue ;
		}
		head_b = last->prev;
	}
	return (return_min_order(index[DESC], index[ASC]));
}

int	ft_simulate_b_to_a(t_stack *stack_a, t_stack *stack_b)
{
	t_double_list	*last;
	t_double_list	*head_a;
	int				index[2];

	last = ft_find_last(stack_a->head_stack);
	index[0] = 0;
	head_a = stack_a->head_stack;
	while (stack_b->head_stack->element > head_a->element)
	{
		index[ASC]++;
		head_a = head_a->next;
	}
	head_a = stack_a->head_stack;
	index[1] = 0;
	while (stack_b->head_stack->element > head_a->element)
	{
		if (index[DESC]++ == 0)
		{
			head_a = last;
			continue ;
		}
		head_a = last->prev;
	}
	return (return_min_order(index[DESC], index[ASC]));
}

int	ft_simulate_shortest_path(t_stack *stack_first, t_stack *stack_second)
{
	if (stack_first->str_id[0] == STACK_A[0])
		return (ft_simulate_b_to_a(stack_first, stack_second));
	return (ft_simulate_a_to_b(stack_second, stack_first));
}

void	ft_sort_four(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	char	*last_operation;
	int		index;

	call_double_operation(stack_first, stack_second,
		&push_swap->operations.operations_main, P_OP);
	ft_find_min_max(stack_first);
	ft_sort_three(stack_first,
		&push_swap->operations.operations_main);
	if (stack_second->head_stack->element == push_swap->global_max)
	{
		call_double_operation(stack_second, stack_first, 
			&push_swap->operations.operations_main, P_OP);

		call_single_operation(stack_first, 
			&push_swap->operations.operations_main, R_OP);
		return ;
	}
	if (ft_simulate_shortest_path(stack_first, stack_second) == ASC)
		last_operation = R_OP;
	else
		last_operation = RR_OP;
	while (stack_second->head_stack->element > stack_first->head_stack->element)
		call_single_operation(stack_first, &push_swap->operations.operations_main,
			last_operation);
	call_double_operation(stack_second, stack_first, &push_swap->operations.operations_main, P_OP);
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
		call_single_operation(stack_first,
			&push_swap->operations.operations_main, last_operation);
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
		ft_sort_five(push_swap);
}