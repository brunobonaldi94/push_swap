/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:58:36 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/26 19:40:39 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_put_element_at_top(t_push_swap *push_swap,
			t_stack *stack, int element)
{
	int		index_element;
	t_list	**operations;

	operations = &push_swap->operations.operations_main;
	index_element = ft_get_index(stack, element);
	if (index_element == stack->size - 1)
	{
		call_single_operation(stack, operations, RR_OP);
		return ;
	}
	if (index_element <= stack->size / 2)
	{
		while (stack->head_stack->element != element)
			call_single_operation(stack, operations, R_OP);
		return ;
	}
	while (stack->head_stack->element != element)
		call_single_operation(stack, operations, RR_OP);
}

void	ft_put_index_at_top(t_push_swap *push_swap,
			t_stack *stack, int index)
{
	t_list	**operations;

	operations = &push_swap->operations.operations_main;
	if (index == stack->size - 1)
	{
		call_single_operation(stack, operations, RR_OP);
		return ;
	}
	if (index <= stack->size / 2)
	{
		while (stack->head_stack->index != index)
			call_single_operation(stack, operations, R_OP);
		return ;
	}
	while (stack->head_stack->index != index)
		call_single_operation(stack, operations, RR_OP);
}

int		ft_get_index(t_stack *stack, int element)
{
	t_double_list	*head;
	int				index;

	head = stack->head_stack;
	index = 0;
	while (head)
	{
		if (head->element == element)
			break ;
		head = head->next;
		index++;
	}
	if (index > stack->size)
		return (-1);
	return (index);
}

void	ft_find_min_max(t_stack *stack)
{
	t_double_list	*head;

	head = stack->head_stack;
	stack->max = INT_MIN;
	stack->min = INT_MAX;
	while (head)
	{
		set_min_max(stack, head->element);
		head = head->next;
	}
}
