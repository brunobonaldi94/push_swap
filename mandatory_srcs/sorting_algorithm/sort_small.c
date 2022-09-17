/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:35:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/16 21:05:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	ft_sort_small(t_stack *stack_a)
{
	if (stack_a->size == 1)
		return ;
	else if (stack_a->size == 2)
	{
		if (stack_a->head_stack->element > stack_a->head_stack->next->element)
			call_single_operation(stack_a, SA);
	}
	else
		ft_sort_three(stack_a);
}