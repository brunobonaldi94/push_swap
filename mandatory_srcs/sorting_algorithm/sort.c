/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/11 23:55:45 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_upcoming(t_stack *stack, char *operation)
{
	int	current_element;

	if (ft_head_is_null(stack->head_stack))
		return ;
	if (ft_is_single_node(stack->head_stack))
	{
		init_min_max(stack, stack->head_stack->element);
		return ;
	}
	current_element = stack->head_stack->element;
	if (current_element < stack->head_stack->next->element)
		call_single_operation(stack, operation);
	set_min_max(stack, current_element);
}

int	partition_high(t_stack *stack_a, t_stack *stack_b)
{
	int				pivot;
	t_double_list	*last;
	int				is_all_sorted;

	last = ft_find_last(stack_a->head_stack);
	pivot = last->element;
	call_single_operation(stack_a, RA);
	is_all_sorted = FALSE;
	while (stack_a->head_stack != last)
	{
		if (stack_a->head_stack->element > pivot)
		{
			call_double_operation(stack_a, stack_b, PB);
			sort_upcoming(stack_b, SB);
		} 
		else 
			call_single_operation(stack_a, RA);	
	}
	call_double_operation(stack_a, stack_b, PB);
	sort_upcoming(stack_b, SB);
	return (is_all_sorted);
}

t_stack	*partition_low(t_stack *stack_a, t_stack *stack_b)
{
	int				pivot;
	t_double_list	*head;

	if (ft_head_is_null(stack_a->head_stack))
		return (NULL);
	pivot = stack_a->head_stack->element;
	head = stack_a->head_stack;
	call_single_operation(stack_a, RA);
	while (stack_a->head_stack != head)
	{
		if (stack_a->head_stack->element < pivot)
		{
			call_double_operation(stack_a, stack_b, PB);
			sort_upcoming(stack_b, SB);
		} 
		else 
			call_single_operation(stack_a, RA);	
	}
	set_min_max(stack_a, stack_a->head_stack->element);
	call_double_operation(stack_a, stack_b, PB);
	return (stack_a);
}

void	ft_sort_recursive2(t_stack *stack_first, t_stack *stack_second)
{
	while (stack_first->size >= 1)
		partition_high(stack_first, stack_second);
	return ;
}

void	ft_sort_iterative(t_stack *stack_first, t_stack *stack_second)
{
	t_stack	*stack;

	stack = stack_first;
	while (stack)
		stack = partition_low(stack, stack_second);
	while (stack_second->head_stack)
		call_double_operation(stack_second, stack_first, PA);
}

void	ft_sort(t_push_swap *push_swap)
{
	ft_print_all_stack(push_swap);
	if (push_swap->stack_a.size == 1)
		return ;
	ft_sort_iterative(&push_swap->stack_a, &push_swap->stack_b);
	//ft_print_all_stack(push_swap);
	ft_clear_all_stack(push_swap);
}