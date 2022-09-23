/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_percentiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:24:32 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/22 21:21:00 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_refill_aux_list(t_stack *stack_aux, t_stack *stack)
{
	t_double_list	*last;

	ft_clear_stack(stack_aux);
	last = ft_find_last(stack->head_stack);
	ft_fill_aux_list(stack_aux, last);
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

