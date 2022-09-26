/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:22:43 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/25 13:09:00 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	ft_find_median(t_push_swap *push_swap, t_stack *stack, int fill_index)
{
	int				median_index;
	double			elements[2];
	int				index;
	t_double_list	*head;

	if (ft_stack_is_empty(stack) || stack->size <= 2)
		return (INT_MAX);
	median_index = stack->size / 2;
	index = 0;
	ft_sort_aux_list(push_swap, stack, fill_index);
	head = push_swap->stack_aux.head_stack;
	while (++index < median_index)
		head = head->next;
	elements[1] = head->next->element;
	if (stack->size % 2 == 0)
		elements[0] = head->element;
	else
		elements[0] = elements[1];
	return ((elements[0] + elements[1]) / 2.0);
}

double	ft_find_percentile(t_push_swap *push_swap, t_stack *stack,
			int percentile)
{
	int				median_index;
	double			elements[2];
	int				index;
	t_double_list	*head;

	if (ft_stack_is_empty(stack) || stack->size <= 2)
		return (INT_MAX);
	median_index = stack->size / percentile;
	index = 0;
	head = push_swap->stack_aux.head_stack;
	while (++index < median_index)
		head = head->next;
	elements[1] = head->next->element;
	if (stack->size % 2 == 0)
		elements[0] = head->element;
	else
		elements[0] = elements[1];
	return ((elements[0] + elements[1]) / 2.0);
}
