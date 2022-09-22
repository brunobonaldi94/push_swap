/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_percentiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:24:32 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/21 22:29:01 by bbonaldi         ###   ########.fr       */
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

void	ft_fill_aux_list(t_stack *stack_aux, t_double_list *last_a)
{
	t_double_list	*new_node;

	while (last_a)
	{
		new_node = ft_create_node(last_a->element);
		ft_push_stack(stack_aux, new_node);
		last_a = last_a->prev;
	}
}

void	ft_refill_aux_list(t_stack *stack_aux, t_stack *stack)
{
	t_double_list	*last;

	ft_clear_stack(stack_aux);
	last = ft_find_last(stack->head_stack);
	ft_fill_aux_list(stack_aux, last);
}

void	ft_fill_aux_indexes(t_stack *stack_aux, t_stack *stack_a)
{
	t_double_list	*head;
	t_double_list	*head_a;
	int				index;

	head = stack_aux->head_stack;
	index = 0;
	while (head)
	{
		head->index = index++;
		head = head->next;
	}
	head = stack_aux->head_stack;
	head_a = stack_a->head_stack;
	while (head_a)
	{
		head = stack_aux->head_stack;
		while (head)
		{
			if (head_a->element == head->element)
				head_a->index = head->index;
			head = head->next;
		}
		head_a = head_a->next;
	}
}

void	ft_set_unordered_count(t_double_list **head, t_percentile *perc, 
			int value_another_percentile)
{
	double			percentile_const;

	percentile_const = perc->percentile_const;
	int index = 0;
	while (percentile_const >= 0 && *head)
	{
		if (perc->percentile_id == 1 && (*head)->element <= perc->value)
			perc->count_unordered++;
		else if (perc->percentile_id != 1 
			&& (*head)->element > value_another_percentile && (*head)->element <= perc->value)
			perc->count_unordered++;	 
 		(*head) = (*head)->next;
		percentile_const--;
		index++;
	}
}

void	ft_unordered_percentile_count(t_push_swap *push_swap, int count)
{
	t_double_list	*head_a;
	int				index;
	int				previous_value;

	head_a = push_swap->stack_a.head_stack;
	index = 0;
	previous_value = push_swap->stack_a.min;
	while (index < count)
	{
		if (index >= 1)
			previous_value = push_swap->percentiles[index - 1].value;
		ft_set_unordered_count(&push_swap->stack_a.head_stack, 
			&push_swap->percentiles[index], previous_value);
		index++;
	}
	push_swap->stack_a.head_stack = head_a;
}

double	ft_percentile_const_create(int size, int percentile_count)
{
	double percentile_const;

	percentile_const = 1.0 / (double)percentile_count;
	return (size * percentile_const);
}

void	ft_init_percentiles(t_percentile *perc, int size,
			int percentile_count, int percentile_nbr)
{
	perc->percentile_const = ft_percentile_const_create(size,
		percentile_count);
	perc->count_unordered = 0;
	perc->percentile_id = percentile_nbr;
	perc->value = -1;
}

double	ft_calculate_percentile(t_push_swap *push_swap, t_percentile perc)
{
	double			index_calculation;
	double			elements[2];
	int				index;
	t_double_list	*head;
	double			value;

	index_calculation = perc.percentile_const *
		perc.percentile_id;
 	head = push_swap->stack_aux.head_stack;
	if (push_swap->stack_aux.size % 2 == 0)
		index_calculation--;
	index = 0;
	while (index < index_calculation)
	{
		head = head->next;
		index++;
	}
	elements[0] = head->element;
	if (push_swap->stack_aux.size % 2 == 0 && head->next)
		elements[1] = head->next->element;
	else
		elements[1] = head->element;
	value = (elements[0] + elements[1]) / 2;
	return (value);
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

int		ft_get_index_ordered_of_element(t_stack *stack, int element)
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
	if (head == NULL)
		return (-1);
	return (head->index);
}


int		ft_get_next_index_asc(t_stack *stack, int index_start, int index_max)
{
	index_start++;
	t_double_list	*head;
	int				index;

	head = stack->head_stack;
	while (index_start <= index_max)
	{
		head = stack->head_stack;
		index = 0;
		while (head)
		{
			if (head->index == index_start)
				return (index);
			head = head->next;
			index++;
		}
		index_start++;
	}
	if (index_start > index_max)
		return (-1);
	return (index);
}

int		ft_get_previous_index_asc(t_stack *stack, 
			int index_start, int index_min)
{
	index_start--;
	t_double_list	*head;
	int				index;

	head = stack->head_stack;
	while (index_start >= index_min)
	{
		head = stack->head_stack;
		index = 0;
		while (head)
		{
			if (head->index == index_start)
				return (index);
			head = head->next;
			index++;
		}
		index_start--;
	}
	if (index_start < index_min)
		return (-1);
	return (index);
}

int		ft_get_index_from_next_index(t_stack *stack, int index_start,
			int order)
{
	int				index;
	int				index_max;

	index = -1;
	if (order == ASC)
	{
		index_max = ft_get_index_ordered_of_element(stack, stack->max);
		return (ft_get_next_index_asc(stack, index_start, index_max));
	}
	return (index);
}

int		ft_get_index_from_previous_index(t_stack *stack, int index_start,
			int order)
{
	int				index;
	int				index_min;

	index = -1;
	if (order == ASC)
	{
		index_min = ft_get_index_ordered_of_element(stack, stack->min);
		return (ft_get_previous_index_asc(stack, index_start, index_min));
	}
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

double	ft_recalculate_percentile(t_push_swap *push_swap, 
		t_stack *stack, double index_calculation)
{
	double			elements[2];
	t_double_list	*head;
	int				index;
	
	
	if (ft_is_single_node(stack->head_stack))
		return (stack->head_stack->element);
	if (stack->size == 2)
		return ((stack->head_stack->element + 
			stack->head_stack->next->element) / 2);
 	ft_find_min_max(stack);
	ft_clear_stack(&push_swap->stack_aux);
	ft_sort_aux_list(push_swap, stack, FALSE);
	if (push_swap->stack_aux.size % 2 == 0)
		index_calculation--;
	head = push_swap->stack_aux.head_stack;
	index = 0;
	while (index < index_calculation)
	{
		head = head->next;
		index++;
	}
 	elements[0] = head->element;
	if (push_swap->stack_aux.size % 2 == 0 && head->next)
		elements[1] = head->next->element;
	else
		elements[1] = head->element;
	return (elements[0] + elements[1]) / 2;
}

void	ft_clear_percentiles(t_push_swap *push_swap)
{
	free(push_swap->percentiles);
}

void	ft_sort_aux_list(t_push_swap *push_swap,
			t_stack *stack, int fill_index)
{
	t_double_list	*last;

	if (push_swap->stack_aux.head_stack != NULL)
		ft_clear_stack(&push_swap->stack_aux);
	last = ft_find_last(stack->head_stack);
	ft_fill_aux_list(&push_swap->stack_aux, last);
	ft_quick_sort_recursive(push_swap->stack_aux.head_stack, last);
	if (fill_index)
		ft_fill_aux_indexes(&push_swap->stack_aux, stack);
}

void	ft_set_percentile_count(int size, int *percentile_count)
{
	if (size <= 10)
		*percentile_count = 1;
	else if (size <= 100)
		*percentile_count = 3;
	else if (size <= 500)
		*percentile_count = 4;
	else
		*percentile_count = 5;
}

void	ft_find_percentiles(t_push_swap *push_swap)
{
	int	size;
	int index;

	size = push_swap->stack_a.size;
	ft_sort_aux_list(push_swap, &push_swap->stack_a, TRUE);
	ft_set_percentile_count(size, &push_swap->percentiles_count);
	push_swap->percentiles = (t_percentile *)malloc(sizeof(t_percentile) 
		* push_swap->percentiles_count);
	index = 0;
	while (index < push_swap->percentiles_count)
	{
		ft_init_percentiles(&push_swap->percentiles[index], size,
			push_swap->percentiles_count + 1, index + 1);
		push_swap->percentiles[index].value = ft_calculate_percentile(push_swap, 
			push_swap->percentiles[index]);
		index++;
	}
 	ft_unordered_percentile_count(push_swap, push_swap->percentiles_count);
}