/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:43:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/13 20:41:43 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_stack_is_empty(t_stack *stack)
{
	return (stack->size == 0);
}

void	ft_bubble_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	temp;
	int	i;

	i = 0;
	while (ft_stack_is_empty(stack_a) == FALSE)
	{

		if (i == 0)
		{
			call_double_operation(stack_a, stack_b, PB);
			i++;
			continue;
		}
		temp = stack_a->head_stack->element;
		call_single_operation(stack_a, RA);
		while (ft_stack_is_empty(stack_b) == FALSE && stack_b->head_stack->element < temp)
			call_double_operation(stack_b, stack_a, PA);
		call_single_operation(stack_a, RRA);
		call_double_operation(stack_a, stack_b, PB);
		i++;
	}
	while (ft_stack_is_empty(stack_b) != FALSE)
		call_double_operation(stack_b, stack_a, PA);
}

