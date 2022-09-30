/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_chunks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:27:49 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/29 23:30:03 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_count_big_of_chuncks(double size, int min_size)
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

void	ft_send_back_sorted_big_to_a(t_stack *stack_first,
			t_stack *stack_second, t_list **operations)
{
	while (ft_stack_is_empty(stack_second) == FALSE)
		call_double_operation(stack_second, stack_first, operations, P_OP);
}


void	ft_send_half_big_to_b(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second, int is_first_half)
{
	int		b_size_adder;
	int		starting_size;
	int		half_index;

	b_size_adder = stack_first->size / 2;
	starting_size = stack_second->size;
	half_index = (push_swap->size + stack_second->size) / 2;
	while (stack_second->size < (starting_size + b_size_adder))
	{
		ft_less_operations_for_below_index(push_swap, stack_first,
			stack_second, half_index);
		if (is_first_half && stack_second->head_stack->index < half_index / 2)
			call_single_operation(stack_second, 
				&push_swap->operations.operations_main, R_OP);
	}
}

void	ft_send_big_chunks_to_b(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int			index;
	int			starting_size;

	starting_size = stack_second->size;
	index = 0;
	push_swap->count_of_chunks = ft_count_big_of_chuncks(stack_first->size, 1);
	push_swap->chunks = (t_chunks *)malloc(sizeof(t_chunks) *
		push_swap->count_of_chunks);
	while (index < push_swap->count_of_chunks)
	{
		ft_send_half_big_to_b(push_swap, stack_first, stack_second, index == 0);
		push_swap->chunks[index].qty_elements = stack_second->size
			- starting_size;
		starting_size = stack_second->size;
		index++;
	}
}

void	ft_rechunk_big(t_push_swap *push_swap,
			t_stack *stack_b, t_stack *stack_a)
{
	int	elements_qty;
	int	index_min;
	int	index_adder;
	int	b_starting_size;
	
	elements_qty = 25;
	b_starting_size = stack_b->size;
	stack_b->count_of_chunks = (stack_b->size / elements_qty);
	index_min = ft_get_ordered_index(stack_b, stack_b->min);
	while (stack_b->size > elements_qty)
	{
		ft_less_operations_for_above_index(push_swap, stack_a, stack_b, 
		index_min + elements_qty);
	}
	index_adder = 2;
	while (stack_b->size < b_starting_size)
	{
		while (stack_b->size < elements_qty * index_adder)
		{
			ft_less_operations_for_below_index(push_swap, stack_a, stack_b, 
			(index_min + elements_qty) * index_adder);
		}
		index_adder++;
	}
}

void	ft_sort_chunks_big(t_push_swap *push_swap)
{
	int	count_of_chunks;
	int	qty_elements;
	//int size_op;

	count_of_chunks = push_swap->count_of_chunks - 1;
	while (count_of_chunks)
	{		
		qty_elements = push_swap->chunks[count_of_chunks].qty_elements;
		ft_selection_sort_chunks_index_desc(push_swap, qty_elements);
		count_of_chunks--;
		//size_op = ft_lstsize(push_swap->operations.operations_main);
		//ft_printf("chunk:%d | qty:%d = %d\n",count_of_chunks, qty_elements, size_op);
	}
	qty_elements = push_swap->stack_b.size;
	ft_selection_sort_chunks_index_desc(push_swap, qty_elements);
	//size_op = ft_lstsize(push_swap->operations.operations_main);
	//ft_printf("chunk:%d | qty:%d = %d\n", --count_of_chunks, qty_elements, size_op);
}

void	ft_sort_big_chunks(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	t_list	**operations;
	
	operations = &push_swap->operations.operations_main;
	ft_send_big_chunks_to_b(push_swap, stack_first, stack_second);
	if (stack_first->size <= 3 && stack_second->size <= 3)
	{
		ft_small_sort(stack_first, operations);
		ft_small_sort(stack_second, operations);
		ft_send_back_sorted_big_to_a(stack_first, stack_second, operations);
		return ;
	}
	if (stack_first->size <= 3)
		ft_small_sort(stack_first, operations);
	ft_sort_chunks_big(push_swap);
}