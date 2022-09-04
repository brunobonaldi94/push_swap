/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:43:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/04 23:06:55 by bbonaldi         ###   ########.fr       */
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

t_double_list *partition_low(t_double_list *head)
{
	int	pivot;
	t_double_list *right_nodes;
	t_double_list *left_nodes;

	pivot = head->element;
	left_nodes = head;
	right_nodes = head->next;
	while (right_nodes != NULL)
	{
		if (right_nodes->element < pivot)
		{
			if (left_nodes)
				left_nodes = left_nodes->next;
			else
				left_nodes = head;
			swap(&left_nodes->element, &right_nodes->element);
		}
		right_nodes = right_nodes->next;
	}
	if (!left_nodes)
		return (NULL);
	swap(&left_nodes->element, &head->element);
	return (left_nodes);
}

void	ft_quick_sort_recursive(t_double_list *head, t_double_list *last)
{
	t_double_list	*partition_node;

	if (last != NULL && head != last && head != last->next)
	{
		partition_node = partition_low(head);
		ft_quick_sort_recursive(head, partition_node->prev);
		ft_quick_sort_recursive(partition_node->next, last);
	}
}

void	ft_quick_sort(t_push_swap *push_swap)
{
	t_double_list *last;

	last = ft_find_last(push_swap->stack_a.head_stack);
	ft_quick_sort_recursive(push_swap->stack_a.head_stack, last);
	return ;
}