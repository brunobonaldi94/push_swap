/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:26:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/21 19:03:56 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insertion_sort(t_stack *stack_a, t_stack *stack_b,
			t_list **operations)
{
	while (stack_a->size != 0)
	{
		int cur = stack_a->head_stack->element;
		call_single_operation(stack_a, operations, R_OP);
		while (stack_b->size != 0 && stack_b->head_stack->element < cur)
		{
			call_double_operation(stack_b, stack_a, operations, P_OP);
		}
		call_single_operation(stack_a, operations, RR_OP);
		call_double_operation(stack_a, stack_b, operations, P_OP);
	} 
}