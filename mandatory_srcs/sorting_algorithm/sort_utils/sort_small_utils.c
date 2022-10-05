/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:30:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 21:30:35 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_small_sort(t_stack *stack, t_list **operations)
{
	if (stack->size == 2)
		ft_sort_two(stack, operations);
	if (stack->size == 3)
	{
		if (stack->str_id[0] == STACK_A[0])
			ft_sort_three(stack, operations);
		else
			ft_sort_three_desc(stack, operations);
	}
}
