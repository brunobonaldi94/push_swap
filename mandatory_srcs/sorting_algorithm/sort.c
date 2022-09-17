/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/17 00:04:30 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_is_sorted(t_stack *stack, int order)
{
	int				is_sorted;
	t_double_list	*head;
	t_double_list	*next;

	is_sorted = TRUE;
	head = stack->head_stack;
	if (head == NULL)
		return (is_sorted);
	next = head->next;
	while (next)
	{	if (order == ASC && head->element > next->element)
			return (FALSE);
		if (order == DESC && head->element < next->element)
			return (FALSE);
		head = head->next;
		next = head->next;
	}
	return (is_sorted);
}

void	sort_b(t_stack *stack, t_percentile perc)
{
	int	current_element;

	if (ft_head_is_null(stack->head_stack))
		return ;
	current_element = stack->head_stack->element;	
	set_min_max(stack, current_element);
	if (ft_is_single_node(stack->head_stack))
		return ;
	if (current_element <= perc.value)
	{
		call_single_operation(stack, RB);
		return ;
	}
	if (current_element < stack->head_stack->next->element)
		call_single_operation(stack, SB);
}

void	sort_a(t_stack *stack)
{
	int	current_element;
	int count_of_RAs;

	count_of_RAs = 0;
	if (ft_head_is_null(stack->head_stack))
		return ;
	current_element = stack->head_stack->element;	
	set_min_max(stack, current_element);
	if (ft_is_single_node(stack->head_stack))
		return ;
	while (current_element > stack->head_stack->next->element)
	{
		call_single_operation(stack, SA);
		call_single_operation(stack, RA);
		count_of_RAs++;
	}
	while (stack->head_stack->element != stack->min)
	{
		if (count_of_RAs >= (stack->size / 2))
			call_single_operation(stack, RA);
		else
			call_single_operation(stack, RRA);
	}
}

int	ft_diff_index(t_stack *stack, double perc_const, int current_index, int order)
{
	int	perc_index;
	if (order == DESC)
	{
		perc_index = (int)((perc_const - current_index) + 0.5) - 1;
		return ((perc_index - stack->head_stack->index) - 
				(perc_index - current_index));
	}
		
	else if (order == ASC)
		return (stack->head_stack->index - current_index);
	return (FALSE);
}

int ft_convert_percentile_cost_to_int(double perc_const)
{
	int	perc_index;

	perc_index = (int)((perc_const) + 0.5) - 1;
	return (perc_index);
}

void	send_to_b(t_push_swap *push_swap, int percentile)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int		index;
	int		size;

	index = 0;
	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	size = stack_a->size;
	while (index < size)
	{
		if (push_swap->stack_a.head_stack->element <= percentile)
			call_double_operation(stack_a, stack_b, PB);
		else
			call_single_operation(stack_a, RA);
		index++;
	}
}

void	send_to_b_index(t_push_swap *push_swap, int max_index)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int		index;
	int		size;

	index = 0;
	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	size = stack_a->size;
	while (index < size)
	{
		if (push_swap->stack_a.head_stack->index <= max_index)
			call_double_operation(stack_a, stack_b, PB);
		else
			call_single_operation(stack_a, RA);
		index++;
	}
}

void	send_to_a_index(t_push_swap *push_swap, int min_index)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int		index;
	int		size;

	index = 0;
	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	size = stack_b->size;
	while (index < size)
	{
		if (push_swap->stack_b.head_stack->index > min_index)
			call_double_operation(stack_b, stack_a, PA);
		else
			call_single_operation(stack_b, RB);
		index++;
	}
}

void	send_to_a(t_push_swap *push_swap, int percentile)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int		index;
	int		size;

	index = 0;
	stack_a = &push_swap->stack_a;
	stack_b = &push_swap->stack_b;
	size = stack_b->size;
	while (index < size)
	{
		if (push_swap->stack_b.head_stack->element > percentile)
			call_double_operation(stack_b, stack_a, PA);
		else
			call_single_operation(stack_b, RB);
		index++;
	}
}


void	ft_sort_big(t_push_swap *push_swap)
{
	int index;
 	send_to_b(push_swap, push_swap->percentiles[1].value);
	send_to_a(push_swap, push_swap->percentiles[0].value);
	// send_to_a(push_swap, push_swap->percentiles[0].value / 2);
	index = 0;
	while (push_swap->stack_b.size >= 2)
	{
		send_to_b_index(push_swap, push_swap->percentiles[0].percentile_const / ((2 + index + 1)));
		send_to_a_index(push_swap, push_swap->percentiles[0].percentile_const / ((2 + index + 1) * 2));
		index++;
	}
	// int max_operations = push_swap->median.percentile_const;
	// while (max_operations >= 0)
	// {
	// 	if (stack_b->head_stack->index < stack_b->head_stack->next->index)
	// 		call_single_operation(stack_b, SB);
	// 	call_double_operation(stack_b, stack_a, PA);
	// 	max_operations--;
	// }

}

void	ft_sort(t_push_swap *push_swap)
{
	//ft_print_all_stack(push_swap);
	

	if (push_swap->is_sorted == TRUE)
		return ;
	if (push_swap->stack_a.size <= 3)
		ft_sort_small(&push_swap->stack_a);
	else
	{
		ft_find_percentiles(push_swap);
		ft_sort_big(push_swap);
	}
	//ft_print_all_stack(push_swap);
	//ft_printf("%d|%d|%d", push_swap->first_quarter.value,push_swap->median.value,push_swap->third_quarter.value);
	ft_clear_all_stack(push_swap);
	ft_clear_percentiles(push_swap);
}