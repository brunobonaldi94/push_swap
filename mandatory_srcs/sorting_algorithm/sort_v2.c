/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/16 21:15:19 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_b(t_stack *stack, t_percentile perc)
{
	int	current_element;

	if (ft_head_is_null(stack->head_stack))
		return ;
	current_element = stack->head_stack->element;	
	set_min_max(stack, current_element);
	if (ft_is_single_node(stack->head_stack))
		return ;
	if (current_element <= perc.value)
	{
		call_single_operation(stack, RB);
		return ;
	}
	if (current_element < stack->head_stack->next->element)
		call_single_operation(stack, SB);
}

void	sort_a(t_stack *stack)
{
	int	current_element;
	int count_of_RAs;

	count_of_RAs = 0;
	if (ft_head_is_null(stack->head_stack))
		return ;
	current_element = stack->head_stack->element;	
	set_min_max(stack, current_element);
	if (ft_is_single_node(stack->head_stack))
		return ;
	while (current_element > stack->head_stack->next->element)
	{
		call_single_operation(stack, SA);
		call_single_operation(stack, RA);
		count_of_RAs++;
	}
	while (stack->head_stack->element != stack->min)
	{
		if (count_of_RAs >= (stack->size / 2))
			call_single_operation(stack, RA);
		else
			call_single_operation(stack, RRA);
	}
}

void	ft_sort_big(t_push_swap *push_swap)
{
	t_stack *stack_a;
	t_stack *stack_b;

	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	while (stack_b->size <= push_swap->median.percentile_const * 2)
	{
		if (push_swap->stack_a.head_stack->element <= push_swap->median.value)
		{
			call_double_operation(stack_a, stack_b, PB);
			sort_b(stack_b, push_swap->first_quarter);
		}
		else
			call_single_operation(stack_a, RA);
	}
	while (stack_b->size <= push_swap->third_quarter.percentile_const * 3)
	{
		if (push_swap->stack_a.head_stack->element <= push_swap->third_quarter.value)
		{
			call_double_operation(stack_a, stack_b, PB);
			sort_b(stack_b, push_swap->median);
		}
		else
			call_single_operation(stack_a, RA);
	}
	while (stack_a->head_stack->element < stack_a->head_stack->next->element)
	{
		call_single_operation(stack_a, SA);
		call_single_operation(stack_a, RA);
	}

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
		ft_sort_big(push_swap);
	//ft_print_all_stack(push_swap);
	//ft_printf("%d|%d|%d", push_swap->first_quarter.value,push_swap->median.value,push_swap->third_quarter.value);
	ft_clear_all_stack(push_swap);
}