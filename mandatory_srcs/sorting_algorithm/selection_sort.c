/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:27:48 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/26 23:39:38 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_selection_sort_desc(t_push_swap *push_swap,
			t_stack *stack_b, t_stack *stack_a)
{
	t_list	**operations;

	operations = &push_swap->operations.operations_main;
	while (ft_stack_is_empty(stack_b) == FALSE)
	{
		ft_put_element_at_top(push_swap, stack_b, stack_b->max);
		call_double_operation(stack_b, stack_a, operations, P_OP);
		ft_find_min_max(stack_b);
	}
}

void	ft_selection_sort_chunks_desc(t_push_swap *push_swap,
			t_stack *stack_b, t_stack *stack_a, int elements_count)
{
	t_list			**operations;
	t_double_list	*last_aux;

	operations = &push_swap->operations.operations_main;
	ft_sort_aux_list_chunks(push_swap, stack_b, elements_count);
	last_aux = ft_find_last(push_swap->stack_aux.head_stack);
	while (last_aux)
	{
		ft_put_element_at_top(push_swap, stack_b, last_aux->element);
		call_double_operation(stack_b, stack_a, operations, P_OP);
		last_aux = last_aux->prev;
	}
}
