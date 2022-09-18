/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:35:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/17 21:06:25 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack *stack);

void	ft_create_operation(char operation[3], char first_letter,
			char a_or_b)
{
	operation[0] = first_letter;
	operation[1] = a_or_b;
	operation[2] = '\0';
}

void	ft_sort_five(t_push_swap *push_swap)
{
	return (void)(push_swap);
}

void	ft_sort_four(t_push_swap *push_swap, 
			t_stack *stack_first, t_stack *stack_second, char a_or_b)
{
	char	operation[3];
	char	opposite_a_or_b;

	if (a_or_b == STACK_A)
		opposite_a_or_b = STACK_B;
	else
		opposite_a_or_b = STACK_A;
	ft_create_operation(operation, 'p', a_or_b);
	call_double_operation(stack_first, stack_second, operation);
	ft_find_min_max(stack_first);
	ft_sort_three(stack_first);
	if (stack_second->head_stack->element == push_swap->global_max)
	{
		ft_create_operation(operation, 'p', opposite_a_or_b);
		call_double_operation(stack_second, stack_first, operation);
		ft_create_operation(operation, 'r', a_or_b);
		call_single_operation(stack_first, operation);
		return ;
	}
	while (stack_second->head_stack->element > stack_first->head_stack->element)
	{
		ft_create_operation(operation, 'r', a_or_b);
		call_single_operation(stack_first, operation);
	}
	ft_create_operation(operation, 'p', opposite_a_or_b);
	call_double_operation(stack_second, stack_first, operation);
	while (stack_first->head_stack->element != push_swap->global_min)
	{
		ft_create_operation(operation, 'r', a_or_b);
		call_single_operation(stack_first, operation);
	}
}

void	ft_sort_three(t_stack *stack)
{
	int	element_head;
	int	element_next;

	element_head = stack->head_stack->element;
	element_next = stack->head_stack->next->element;
	if (element_head == stack->min && element_next == stack->max)
	{
		call_single_operation(stack, RRA);
		call_single_operation(stack, SA);
	}
	else if (element_head != stack->max && element_next == stack->min)
		call_single_operation(stack, SA);
	else if (element_head != stack->min && element_next == stack->max)
		call_single_operation(stack, RRA);
	else if (element_head == stack->max && element_next == stack->min)
		call_single_operation(stack, RA);
	else if (element_head == stack->max && element_next != stack->min)
	{
		call_single_operation(stack, RA);
		call_single_operation(stack, SA);
	}
}

void	ft_sort_two(t_stack *stack)
{
	if (stack->head_stack->element > stack->head_stack->next->element)
			call_single_operation(stack, SA);
}

void	ft_set_stacks(t_push_swap *push_swap, t_stack	**stack_first,
			t_stack **stack_second, char a_or_b)
{
	if (a_or_b == STACK_A)
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

void	ft_sort_small(t_push_swap *push_swap, char a_or_b)
{
	t_stack	*stack_first;
	t_stack	*stack_second;

	ft_set_stacks(push_swap, &stack_first, &stack_second, a_or_b);
	if (push_swap->stack_a.size == 1)
		return ;
	else if (push_swap->stack_a.size == 2)
		ft_sort_two(stack_first);
	else if (push_swap->stack_a.size == 3)
		ft_sort_three(stack_first);
	else if (push_swap->stack_a.size == 4)
		ft_sort_four(push_swap, stack_first, stack_second, a_or_b);
	else
		ft_sort_five(push_swap);
}