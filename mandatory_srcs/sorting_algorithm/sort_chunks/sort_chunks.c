/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:43:35 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/28 23:07:39 by bbonaldi         ###   ########.fr       */
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
	int		half_index;

	b_size_adder = stack_first->size / 2;
	starting_size = stack_second->size;
	half_index = (push_swap->size + stack_second->size) / 2;
	while (stack_second->size < (starting_size + b_size_adder))
	{
		ft_less_operations_for_below_index(push_swap, stack_first,
			stack_second, half_index);
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

void	ft_sort_chunks(t_push_swap *push_swap)
{
	int	count_of_chunks;
	int	qty_elements;
	int size_op;

	count_of_chunks = push_swap->count_of_chunks;
	while (count_of_chunks)
	{		
		qty_elements = push_swap->chunks[count_of_chunks].qty_elements;
		ft_selection_sort_chunks_index_desc(push_swap, qty_elements);
		count_of_chunks--;
		size_op = ft_lstsize(push_swap->operations.operations_main);
		ft_printf("chunk:%d | qty:%d = %d\n",count_of_chunks, qty_elements, size_op);
	}
	if (push_swap->stack_a.size != push_swap->size)
	{
		qty_elements = push_swap->stack_b.size;
		ft_selection_sort_chunks_index_desc(push_swap, qty_elements);
		size_op = ft_lstsize(push_swap->operations.operations_main);
		ft_printf("chunk:%d = %d\n",--count_of_chunks, size_op);
	}
}

void	ft_send_chunks_to_b(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int			index;
	int			starting_size;

	starting_size = stack_second->size;
	index = 0;
	push_swap->count_of_chunks = ft_count_of_chuncks(stack_first->size, 1);
	push_swap->chunks = (t_chunks *)malloc(sizeof(t_chunks) *
		push_swap->count_of_chunks);
	while (index < push_swap->count_of_chunks)
	{
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
	
	operations = &push_swap->operations.operations_main;
	ft_send_chunks_to_b(push_swap, stack_first, stack_second);
	if (stack_first->size <= 3 && stack_second->size <= 3)
	{
		ft_small_sort(stack_first, operations);
		ft_small_sort(stack_second, operations);
		ft_send_back_sorted_to_a(stack_first, stack_second, operations);
		return ;
	}
	if (stack_first->size <= 3)
		ft_small_sort(stack_first, operations);
	ft_sort_chunks(push_swap);
}