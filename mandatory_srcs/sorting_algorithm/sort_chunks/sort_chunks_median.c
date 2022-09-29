/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:43:35 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/27 23:59:10 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_send_back_sorted_to_a(t_stack *stack_first,
			t_stack *stack_second, t_list **operations)
{
	while (ft_stack_is_empty(stack_second) == FALSE)
		call_double_operation(stack_second, stack_first, operations, P_OP);
}

int	ft_count_elements_below(t_stack *stack, double element)
{
	int				count;
	t_double_list	*head;

	head = stack->head_stack;
	count = 0;
	while (head)
	{
		if (head->element < element)
			count++;
		head = head->next;
	}
	return (count);
}

int	ft_count_elements_between(t_stack *stack, double low, double high)
{
	int				count;
	t_double_list	*head;

	head = stack->head_stack;
	count = 0;
	while (head)
	{
		if (head->element >= low && head->element < high)
			count++;
		head = head->next;
	}
	return (count);
}


void	ft_send_half_to_b(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int		b_size_adder;
	int		starting_size;

	b_size_adder = stack_first->size / 2;
	starting_size = stack_second->size;
	while (stack_second->size < (starting_size + b_size_adder))
	{
		ft_less_operations_for_next_below_median(push_swap, stack_first,
			stack_second, push_swap->median);
	}
}

void	ft_clear_inner_chunks(t_stack *stack)
{
	free(stack->inner_chunks.median);
	free(stack->inner_chunks.qty_elements);
}

void	ft_clear_chunks(t_push_swap *push_swap)
{
	free(push_swap->chunks);
	ft_clear_inner_chunks(&push_swap->stack_a);
	ft_clear_inner_chunks(&push_swap->stack_b);
}

int	ft_count_of_chuncks(double size, int min_size)
{
	int		index;

	index = 0;
	while (size > min_size)
	{
		index++;
		size /= 2.0;
	}
	return (index);
}

void	ft_sort_chunks(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int	count_of_chunks;
	int	qty_elements;

	count_of_chunks = push_swap->count_of_chunks - 1;
	while (count_of_chunks >= 0)
	{
		qty_elements = push_swap->chunks[count_of_chunks].qty_elements - 1;
		ft_selection_sort_chunks_desc(push_swap, stack_second, stack_first,
			qty_elements);
		count_of_chunks--;
	}
}

void	ft_rotate_rev_b(t_push_swap *push_swap, 
			t_stack *stack_b, int count_rotate)
{
	while (count_rotate)
	{
		call_single_operation(stack_b, &push_swap->operations.operations_main, RR_OP);
		count_rotate--;
	}
}

void	ft_send_last_b(t_push_swap *push_swap, t_stack *stack_b)
{
	int	index;
	int	index_above;
	int	index_below;

	index = stack_b->count_of_chunks - 1;
	index_below = 0;
	index_above = 0;
	while (index)
	{
		index_above = 0;
		index_below = 0;
		while (index_above < stack_b->inner_chunks.qty_elements[index])
		{
			if (stack_b->head_stack->element < stack_b->inner_chunks.median[index])
			{
				call_single_operation(stack_b,
				&push_swap->operations.operations_main, R_OP);
				index_below++;
			}
			else
			{
				call_double_operation(stack_b, &push_swap->stack_a, 
				&push_swap->operations.operations_main, P_OP);
				index_above++;
			}
		}
		ft_selection_sort_chunks_asc(push_swap, 
		&push_swap->stack_a, index_above - 1);
		ft_print_stack(&push_swap->stack_a);
		index--;
	}

}

void	ft_rechunks_in_smaller(t_push_swap *push_swap, t_stack *stack_b,
			int qty_elements)
{
	int		index;
	double	perc_fraction;
	//int		sum_elements;

	index = 0;
	//sum_elements = 0;
	stack_b->count_of_chunks = qty_elements / 20;
	stack_b->inner_chunks.median = (double *)malloc(sizeof(double)
		* stack_b->count_of_chunks);
	stack_b->inner_chunks.qty_elements = (int *)malloc(sizeof(int)
		* stack_b->count_of_chunks);
	while (index < stack_b->count_of_chunks)
	{
		perc_fraction = (double)(index + 1) / (double)stack_b->count_of_chunks;
		stack_b->inner_chunks.median[index] = ft_find_percentile_chunck(push_swap,
			stack_b, qty_elements, perc_fraction);
		
		// stack_b->inner_chunks.qty_elements[index] = perc_fraction * qty_elements;
		// if (index > 0)
		// {
		// 	sum_elements += stack_b->inner_chunks.qty_elements[index - 1];
		// 	stack_b->inner_chunks.qty_elements[index] -= sum_elements;
		// }
		if (index == stack_b->count_of_chunks - 1)
		{
			stack_b->inner_chunks.qty_elements[index] = 
			ft_count_elements_between(stack_b,
			stack_b->inner_chunks.median[index], (double)INT_MAX + 1);
		}
		else if (index == 0)
			stack_b->inner_chunks.qty_elements[index] = 
			ft_count_elements_between(stack_b, (double)INT_MIN - 1,
			stack_b->inner_chunks.median[index]);
		else
			stack_b->inner_chunks.qty_elements[index] = 
			ft_count_elements_between(stack_b, stack_b->inner_chunks.median[index - 1],
			stack_b->inner_chunks.median[index]);
		
		index++;
	}
	ft_send_last_b(push_swap, stack_b);
	//ft_selection_sort_chunks_desc(push_swap, stack_b, stack_a, qty_elements);
}

void	ft_sort_big_chunks(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int	count_of_chunks;
	int	qty_elements;

	count_of_chunks = push_swap->count_of_chunks - 1;
	while (count_of_chunks >= 0)
	{
		qty_elements = push_swap->chunks[count_of_chunks].qty_elements - 1;
		if (qty_elements <= 50)
		{
			ft_selection_sort_chunks_desc(push_swap, stack_second, stack_first,
			qty_elements);
		}
		else
		{
			ft_rechunks_in_smaller(push_swap, stack_second, qty_elements);
		}
		count_of_chunks--;
	}
}

void	ft_send_chunks_to_b(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int			count_of_chunks;
	int			index;
	int			starting_size;

	starting_size = stack_second->size;
	index = 1;
	count_of_chunks = push_swap->count_of_chunks;
	while (index < count_of_chunks)
	{
		push_swap->median = ft_find_median(push_swap, stack_first, FALSE);
		ft_send_half_to_b(push_swap, stack_first, stack_second);
		push_swap->chunks[index].qty_elements = stack_second->size
			- starting_size;
		starting_size = stack_second->size;
		index++;
	}
}

void	ft_sort_small_chunks(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	t_list	**operations;
	int		size;
	
	size = stack_first->size;
	operations = &push_swap->operations.operations_main;
	push_swap->count_of_chunks = ft_count_of_chuncks(stack_first->size, 3);
	push_swap->chunks = (t_chunks *)malloc(sizeof(t_chunks) *
		push_swap->count_of_chunks);
	ft_send_half_to_b(push_swap, stack_first, stack_second);
	push_swap->chunks[0].qty_elements = stack_second->size;
	if (stack_first->size <= 3 && stack_second->size <= 3)
	{
		ft_small_sort(stack_first, operations);
		ft_small_sort(stack_second, operations);
		ft_send_back_sorted_to_a(stack_first, stack_second, operations);
		return ;
	}
	ft_send_chunks_to_b(push_swap, stack_first, stack_second);
	if (stack_first->size <= 3)
		ft_small_sort(stack_first, operations);
	if (size >= 100)
		ft_sort_big_chunks(push_swap, stack_first, stack_second);
	else
		ft_sort_chunks(push_swap, stack_first, stack_second);
}