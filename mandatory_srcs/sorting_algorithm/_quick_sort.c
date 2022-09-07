/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _quick_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:43:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/07 21:04:47 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void swap(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}


t_stack *partition_low_ps(t_stack *stack_a, t_stack *stack_b)
{
	int	pivot;
	t_double_list	*right_nodes;
	t_double_list	*left_nodes;

	pivot = stack_a->head_stack->element;
	left_nodes = stack_a->head_stack;
	right_nodes = stack_a->head_stack->next;
	while (right_nodes != NULL)
	{
		if (right_nodes->element < pivot)
		{
			if (left_nodes)
				left_nodes = left_nodes->next;
			else
				left_nodes = stack_a->head_stack;
			swap(&left_nodes->element, &right_nodes->element);
		}
		right_nodes = right_nodes->next;
	}
	if (!left_nodes)
		return (NULL);
	swap(&left_nodes->element, &stack_a->head_stack->element);
	stack_b->head_stack = left_nodes;
	stack_b->size = stack_a->size;
	return (stack_b);
}
void	ft_quick_sort_ps(t_stack *stack_a, t_double_list *last_a, t_stack *stack_b, t_double_list *last_b)
{
	t_stack	*partition_stack;
	ft_printf("%p", last_b);
	if (last_a != NULL && stack_a->head_stack != last_a && stack_a->head_stack != last_a->next)
	{
		partition_stack = partition_low_ps(stack_a, stack_b);
		ft_quick_sort_ps(stack_a, partition_stack->head_stack->prev, stack_b, last_b);
		ft_quick_sort_ps(&(t_stack){partition_stack->size, partition_stack->head_stack->next}, last_a, stack_b, last_b);
	}
}

void	ft_quick_sort(t_push_swap *push_swap)
{
	t_double_list *last_a;
	t_double_list *last_b;

	ft_printf("----------------------------------------------\n");
	last_a = ft_find_last(push_swap->stack_a.head_stack);
	last_b = ft_find_last(push_swap->stack_b.head_stack);
	ft_quick_sort_ps(&push_swap->stack_a, last_a, &push_swap->stack_b, last_b);
	return ;
}