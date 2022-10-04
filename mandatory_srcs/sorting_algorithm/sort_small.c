/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:35:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 19:50:17 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack *stack, t_list **operations);
void	ft_sort_two(t_stack *stack, t_list **operations);
void	ft_sort_three_desc(t_stack *stack, t_list **operations);

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

void	ft_sort_four(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{

	t_list	**operations;

	operations = &push_swap->operations.operations_main;
 	ft_put_element_at_top(push_swap, stack_first, stack_first->min);
	if (ft_is_sorted(stack_first->head_stack, ASC) == TRUE)
			return ;
	call_double_operation(stack_first, stack_second, operations, P_OP);
	ft_sort_three(stack_first, operations);
	call_double_operation(stack_second, stack_first, operations, P_OP);
}


void	ft_sort_three_desc(t_stack *stack, t_list **operations)
{
	int	element_head;
	int	element_next;

	element_head = stack->head_stack->element;
	element_next = stack->head_stack->next->element;
	if (element_head == stack->min && element_next != stack->max)
	{
		call_single_operation(stack, operations, R_OP);
		call_single_operation(stack, operations, S_OP);
	}
	else if (element_head == stack->min && element_next == stack->max)
		call_single_operation(stack, operations, R_OP);
	else if (element_head != stack->min && element_next == stack->min)
		call_single_operation(stack, operations, RR_OP);
	else if (element_head != stack->max && element_next == stack->max)
		call_single_operation(stack, operations, S_OP);
	else if (element_head == stack->max && element_next == stack->min)
	{
		call_single_operation(stack, operations, S_OP);
		call_single_operation(stack, operations, R_OP);
	}
}


void	ft_sort_three(t_stack *stack, t_list **operations)
{
	int	element_head;
	int	element_next;

	element_head = stack->head_stack->element;
	element_next = stack->head_stack->next->element;
	if (element_head == stack->min && element_next == stack->max)
	{
		call_single_operation(stack, operations, RR_OP);
		call_single_operation(stack, operations, S_OP);
	}
	else if (element_head != stack->max && element_next == stack->min)
		call_single_operation(stack, operations, S_OP);
	else if (element_head != stack->min && element_next == stack->max)
		call_single_operation(stack, operations, RR_OP);
	else if (element_head == stack->max && element_next == stack->min)
		call_single_operation(stack, operations, R_OP);
	else if (element_head == stack->max && element_next != stack->min)
	{
		call_single_operation(stack, operations, R_OP);
		call_single_operation(stack, operations, S_OP);
	}
}


void	ft_sort_two(t_stack *stack, t_list **operations)
{
	if (ft_head_is_null(stack->head_stack)
		|| ft_is_single_node(stack->head_stack))
		return ;
	if (stack->str_id[0] == STACK_B[0])
	{
		if (stack->head_stack->element < stack->head_stack->next->element)
			call_single_operation(stack, operations, S_OP);
		return ;
	}
	if (stack->head_stack->element > stack->head_stack->next->element)
			call_single_operation(stack, operations, S_OP);

}


void	ft_sort_small(t_push_swap *push_swap)
{
	t_stack	*stack_first;
	t_stack	*stack_second;

	stack_first = &push_swap->stack_a;
	stack_second = &push_swap->stack_b;
	if (push_swap->stack_a.size == 1)
		return ;
	if (push_swap->stack_a.size == 2)
		ft_sort_two(stack_first, &push_swap->operations.operations_main);
	else if (push_swap->stack_a.size == 3)
		ft_sort_three(stack_first, &push_swap->operations.operations_main);
	else if (push_swap->stack_a.size == 4)
		ft_sort_four(push_swap, stack_first, stack_second);
}