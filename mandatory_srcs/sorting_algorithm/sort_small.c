/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:35:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:34:04 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_two(t_stack *stack, t_list **operations)
{
	if (ft_head_is_null(stack->head)
		|| ft_is_single_node(stack->head))
		return ;
	if (stack->str_id[0] == STACK_B[0])
	{
		if (stack->head->element < stack->head->next->element)
			ft_call_single_operation(stack, operations, S_OP);
		return ;
	}
	if (stack->head->element > stack->head->next->element)
		ft_call_single_operation(stack, operations, S_OP);
}

void	ft_sort_three(t_stack *stack, t_list **operations)
{
	int	element_head;
	int	element_next;

	element_head = stack->head->element;
	element_next = stack->head->next->element;
	if (element_head == stack->min && element_next == stack->max)
	{
		ft_call_single_operation(stack, operations, RR_OP);
		ft_call_single_operation(stack, operations, S_OP);
	}
	else if (element_head != stack->max && element_next == stack->min)
		ft_call_single_operation(stack, operations, S_OP);
	else if (element_head != stack->min && element_next == stack->max)
		ft_call_single_operation(stack, operations, RR_OP);
	else if (element_head == stack->max && element_next == stack->min)
		ft_call_single_operation(stack, operations, R_OP);
	else if (element_head == stack->max && element_next != stack->min)
	{
		ft_call_single_operation(stack, operations, R_OP);
		ft_call_single_operation(stack, operations, S_OP);
	}
}

void	ft_sort_three_desc(t_stack *stack, t_list **operations)
{
	int	element_head;
	int	element_next;

	element_head = stack->head->element;
	element_next = stack->head->next->element;
	if (element_head == stack->min && element_next != stack->max)
	{
		ft_call_single_operation(stack, operations, R_OP);
		ft_call_single_operation(stack, operations, S_OP);
	}
	else if (element_head == stack->min && element_next == stack->max)
		ft_call_single_operation(stack, operations, R_OP);
	else if (element_head != stack->min && element_next == stack->min)
		ft_call_single_operation(stack, operations, RR_OP);
	else if (element_head != stack->max && element_next == stack->max)
		ft_call_single_operation(stack, operations, S_OP);
	else if (element_head == stack->max && element_next == stack->min)
	{
		ft_call_single_operation(stack, operations, S_OP);
		ft_call_single_operation(stack, operations, R_OP);
	}
}

void	ft_sort_four(t_push_swap *push_swap, t_stack *stack_a,
			t_stack *stack_b)
{
	t_list	**operations;

	operations = &push_swap->operations.main;
	ft_put_element_at_top(push_swap, stack_a, stack_a->min);
	if (ft_is_sorted(stack_a->head, ASC) == TRUE)
		return ;
	ft_call_double_operation(stack_a, stack_b, operations, P_OP);
	ft_sort_three(stack_a, operations);
	ft_call_double_operation(stack_b, stack_a, operations, P_OP);
}

void	ft_sort_small(t_push_swap *push_swap)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	if (push_swap->stack_a.size == 1)
		return ;
	if (push_swap->stack_a.size == 2)
		ft_sort_two(stack_a, &push_swap->operations.main);
	else if (push_swap->stack_a.size == 3)
		ft_sort_three(stack_a, &push_swap->operations.main);
	else if (push_swap->stack_a.size == 4)
		ft_sort_four(push_swap, stack_a, stack_b);
}
