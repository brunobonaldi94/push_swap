/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/15 19:50:53 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_b(t_stack *stack)
{
	int	current_element;
	int	count_of_RBs;

	count_of_RBs = 0;
	if (ft_head_is_null(stack->head_stack))
		return ;
	current_element = stack->head_stack->element;	
	set_min_max(stack, current_element);
	if (ft_is_single_node(stack->head_stack))
		return ;
	if (stack->size > 2 && current_element == stack->min)
	{
		call_single_operation(stack, RB);
		return ;
	}
	if (stack->size == 2 && current_element < stack->head_stack->next->element)
	{
		call_single_operation(stack, SB);
		return ;
	}
	while (current_element < stack->head_stack->next->element)
	{
		call_single_operation(stack, SB);
		call_single_operation(stack, RB);
		count_of_RBs++;
	}
	while (stack->head_stack->element != stack->max)
	{
		if (count_of_RBs >= (stack->size / 2))
			call_single_operation(stack, RB);
		else
			call_single_operation(stack, RRB);
	}
}

void	sort_a(t_stack *stack)
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
	if (current_element > stack->head_stack->next->element)
		call_single_operation(stack, SA);
	set_min_max(stack, current_element);
}

void	partition_low(t_stack *stack_a, t_stack *stack_b)
{
	int				pivot;
	t_double_list	*head;

	if (ft_head_is_null(stack_a->head_stack))
		return ;
	pivot = stack_a->head_stack->element;
	head = stack_a->head_stack;
	call_single_operation(stack_a, RA);
	while (stack_a->head_stack != head)
	{
		if (stack_a->head_stack->element < pivot)
		{
			call_double_operation(stack_a, stack_b, PB);
			sort_b(stack_b);
		}
		else
			call_single_operation(stack_a, RA);
	}
	set_min_max(stack_a, stack_a->head_stack->element);
	call_double_operation(stack_a, stack_b, PB);
}

void	ft_sort_iterative(t_stack *stack_first, t_stack *stack_second)
{
	while (stack_first->head_stack)
		partition_low(stack_first, stack_second);
	while (stack_second->head_stack)
		call_double_operation(stack_second, stack_first, PA);
}

void	ft_sort(t_push_swap *push_swap)
{
	//ft_print_all_stack(push_swap);
	ft_find_percentiles(push_swap);
	if (push_swap->is_sorted == TRUE)
		return ;
	if (push_swap->stack_a.size <= 3)
		ft_sort_small(&push_swap->stack_a);
	else
		ft_sort_iterative(&push_swap->stack_a, &push_swap->stack_b);
		//insertion_sort(&push_swap->stack_a, &push_swap->stack_b);
	//ft_print_all_stack(push_swap);
	ft_printf("%d|%d|%d", push_swap->first_quarter,push_swap->median,push_swap->third_quarter);
	ft_clear_all_stack(push_swap);
}