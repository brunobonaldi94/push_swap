/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_II.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:58:36 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/22 23:13:03 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_save_rotations(t_push_swap *push_swap, t_stack *stack_first,
			int qty_moves, int order)
{
	t_stack			*stack_second;
	t_list			**operations;
	t_double_list	*last_second;

	operations = &push_swap->operations.operations_main;
	stack_second = &push_swap->stack_b;
	last_second = ft_find_last(stack_second->head_stack);
	if (order == ASC)
	{
		while (qty_moves)
		{
			if (stack_second->size > 1 &&
				stack_second->head_stack->element < last_second->element)
			{
				last_second = stack_second->head_stack;
				call_double_operation(stack_first, stack_second,
					operations, R_OP);
			}
			else
				call_single_operation(stack_first, operations, R_OP);
			qty_moves--;
		}
		return ;
	}
	while (qty_moves)
	{
		if (stack_second->size > 1 &&
			stack_second->head_stack->element > last_second->element)
		{
			last_second = last_second->prev;
			call_double_operation(stack_first, stack_second,operations, RR_OP);
		}
		else
			call_single_operation(stack_first, operations, RR_OP);
		qty_moves--;
	}
}

void	ft_find_less_from_rotations_below_median(t_push_swap *push_swap,
	t_stack *stack_first, t_stack *stack_second, double median)
{
	t_double_list	*head;
	t_double_list	*last;
	t_list			**operations;
	int				index_asc;
	int				index_desc;

	index_desc = 0;
	index_asc = 0;
	operations = &push_swap->operations.operations_main;
	head = stack_first->head_stack;
	while (head)
	{
		if (head->element < median)
			break;
		index_asc++;
		head = head->next;
	}
	last = ft_find_last(stack_first->head_stack);
	if (stack_first->head_stack->element > median)
		index_desc++;
	while (last)
	{
		if (last->element < median)
			break ;
		index_desc++;
		last = last->prev;
	}
	if (index_asc == 0)
		call_double_operation(stack_first, stack_second, operations, P_OP);
	if (index_asc <= index_desc)
		ft_save_rotations(push_swap, stack_first, index_asc, ASC);
	else
		ft_save_rotations(push_swap, stack_first, index_desc, DESC);
}

void	ft_less_operations_for_next_below_median(t_push_swap *push_swap,
		t_stack *stack_first, t_stack *stack_second, double median)
{
	t_double_list	*head;
	t_double_list	*last;
	t_list			**operations;
	t_double_list	*last_second;
	

	operations = &push_swap->operations.operations_main;
	head = stack_first->head_stack;
	if (head->element < median)
	{
		call_double_operation(stack_first, stack_second, operations, P_OP);
		return ;
	}
	last = ft_find_last(head);
	last_second = ft_find_last(stack_second->head_stack);
	if (last->element < median)
	{
		if (stack_second->size > 1 && 
			stack_second->head_stack->element < last_second->element)
			call_double_operation(stack_first, stack_second, operations, RR_OP);
		else
			call_single_operation(stack_first, operations, RR_OP);
		call_double_operation(stack_first, stack_second, operations, P_OP);
		return ;
	}
	if (head->next && head->element > head->next->element
		&& head->next->element < median)
	{
		if (stack_second->size > 1 && stack_second->head_stack->element 
			< stack_second->head_stack->next->element)
			call_double_operation(stack_first, stack_second, operations, S_OP);
		else
			call_single_operation(stack_first, operations, S_OP);
		call_double_operation(stack_first, stack_second, operations, P_OP);
		return ;
	}
	ft_find_less_from_rotations_below_median(push_swap, stack_first,
		stack_second, median);
}