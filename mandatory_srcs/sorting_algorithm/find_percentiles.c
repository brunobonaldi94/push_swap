/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_percentiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:24:32 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/15 22:50:29 by bbonaldi         ###   ########.fr       */
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

t_double_list *partition_first(t_double_list *head, t_double_list *last)
{
	int				pivot;
	t_double_list	*right_nodes;
	t_double_list	*left_nodes;

	pivot = head->element;
	left_nodes = head;
	right_nodes = head->next;
	while (right_nodes != last->next)
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
		left_nodes = head;
	swap(&left_nodes->element, &head->element);
	return (left_nodes);
}

void	ft_quick_sort_recursive(t_double_list *head, t_double_list *last)
{
	t_double_list	*partition_node;
	if (last != NULL && head != last && head != last->next)
	{
		partition_node = partition_first(head, last);
		ft_quick_sort_recursive(head, partition_node->prev);
		ft_quick_sort_recursive(partition_node->next, last);
	}
}

void	ft_fill_list(t_stack *stack_ordered, t_double_list *last_a)
{
	t_double_list	*new_node;

	while (last_a)
	{
		new_node = ft_create_node(last_a->element);
		ft_push_stack(stack_ordered, new_node);
		last_a = last_a->prev;
	}
}

void	ft_fill_indexes(t_stack *stack_ordered)
{
	t_double_list	*head;
	int				index;

	head = stack_ordered->head_stack;
	index = 0;
	while (head)
	{
		head->index = index++;
		head = head->next;
	}
}

void	ft_set_unordered_count(t_push_swap *push_swap, t_percentile *perc, 
			int value_another_percentile)
{
	t_double_list	*head;
	double			percentile_const;
	int				move_head_times;

	head = push_swap->stack_a.head_stack;
	percentile_const = perc->percentile_const;
	move_head_times = percentile_const * (perc->percentile_id - 1);
	while (--move_head_times >= 0)
		head = head->next;
	int index = 0;
	while (percentile_const >= 0)
	{
		if (perc->percentile_id == FIRST_QUARTER && head->element <= perc->value)
			perc->count_unordered++;
		else if((perc->percentile_id == MEDIAN || perc->percentile_id == THIRD_QUARTER)
				&& head->element > value_another_percentile && head->element <= perc->value)
			perc->count_unordered++;
		head = head->next;
		percentile_const--;
		index++;
	}
}

void	ft_unordered_percentile_count(t_push_swap *push_swap)
{
	ft_set_unordered_count(push_swap, &push_swap->first_quarter,
		push_swap->stack_a.min);
	ft_set_unordered_count(push_swap, &push_swap->median,
		push_swap->first_quarter.value);
	ft_set_unordered_count(push_swap, &push_swap->third_quarter,
		push_swap->median.value);
}

void	ft_init_percentiles(t_percentile *perc, int size, int percentile_nbr)
{
	perc->count_unordered = 0;
	perc->percentile_const = size * PERCENTILE_CONSTANT;
	perc->percentile_id = percentile_nbr;
	perc->value = -1;
}

int	ft_calculate_percentile(t_push_swap *push_swap, t_percentile perc)
{
	double			index_calculation;
	int				elements[2];
	t_double_list	*head;
	int				value;

	index_calculation = perc.percentile_const *
		perc.percentile_id;
 	head = push_swap->stack_ordered.head_stack;
	while (--index_calculation >= 0)
		head = head->next;
	elements[0] = head->element;
	if (push_swap->stack_ordered.size % 2 == 0 && head->next)
		elements[1] = head->next->element;
	else
		elements[1] = head->element;
	value = (elements[0] + elements[1]) / 2;
	return (value);
}

void	ft_sort_auxiliary_list(t_push_swap *push_swap)
{
	t_double_list	*last_a;

	last_a = ft_find_last(push_swap->stack_a.head_stack);
	ft_fill_list(&push_swap->stack_ordered, last_a);
	ft_quick_sort_recursive(push_swap->stack_ordered.head_stack, last_a);
	ft_fill_indexes(&push_swap->stack_ordered);
}

void	ft_find_percentiles(t_push_swap *push_swap)
{
	int	size;

	size = push_swap->stack_a.size;
	ft_sort_auxiliary_list(push_swap);
	ft_init_percentiles(&push_swap->first_quarter, size, FIRST_QUARTER);
	ft_init_percentiles(&push_swap->median, size, MEDIAN);
	ft_init_percentiles(&push_swap->third_quarter, size, THIRD_QUARTER);
	push_swap->first_quarter.value = ft_calculate_percentile(push_swap,
		push_swap->first_quarter);
	push_swap->median.value = ft_calculate_percentile(push_swap,
		push_swap->median);
	push_swap->third_quarter.value = ft_calculate_percentile(push_swap,
		push_swap->third_quarter);
	ft_unordered_percentile_count(push_swap);
}