/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_percentiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:24:32 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/25 13:18:34 by bbonaldi         ###   ########.fr       */
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

void	ft_calculate_median_and_first_quarter(t_push_swap *push_swap)
{
	ft_sort_aux_list(push_swap, &push_swap->stack_a, TRUE);
	push_swap->median = ft_find_percentile(push_swap, &push_swap->stack_aux, 
		2);
	push_swap->first_quarter = ft_find_percentile(push_swap,
		&push_swap->stack_aux, 4);
}

