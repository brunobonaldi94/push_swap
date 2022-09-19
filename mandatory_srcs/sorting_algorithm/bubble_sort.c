/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:43:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/18 19:57:31 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_bubble_sort(t_stack *stack_a, t_stack *stack_b, t_list **operations)
{
	int	temp;
	int	i;

	i = 0;
	while (ft_stack_is_empty(stack_a) == FALSE)
	{

		if (i == 0)
		{
			call_double_operation(stack_a, stack_b, operations, P_OP);
			i++;
			continue;
		}
		temp = stack_a->head_stack->element;
		call_single_operation(stack_a, operations, R_OP);
		while (ft_stack_is_empty(stack_b) == FALSE && stack_b->head_stack->element < temp)
			call_double_operation(stack_b, stack_a, operations, P_OP);
		call_single_operation(stack_a, operations, RR_OP);
		call_double_operation(stack_a, stack_b, operations, P_OP);
		i++;
	}
	while (ft_stack_is_empty(stack_b) != FALSE)
		call_double_operation(stack_b, stack_a, operations, P_OP);
}

