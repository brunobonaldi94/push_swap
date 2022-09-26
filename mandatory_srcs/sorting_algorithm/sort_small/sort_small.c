/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:35:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/25 21:48:35 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack *stack, t_list **operations);
void	ft_sort_two(t_stack *stack, t_list **operations);
void	ft_sort_three_desc(t_stack *stack, t_list **operations);

int	return_min_order(int desc, int asc)
{
	if (desc < asc)
		return (DESC);
	return (ASC);
}

int	ft_simulate_a_to_b(t_stack *stack_a, t_stack *stack_b)
{
	t_double_list	*last;
	t_double_list	*head;
	int				index[2];

	last = ft_find_last(stack_b->head_stack);
	index[0] = 0;
	head = stack_b->head_stack;
	while (stack_a->head_stack->element < head->element)
	{
		index[ASC]++;
		head = head->next;
	}
	head = stack_b->head_stack;
	index[1] = 0;
	while (stack_a->head_stack->element < head->element)
	{
		if (index[DESC]++ == 0)
		{
			head = last;
			continue ;
		}
		head = last->prev;
	}
	return (return_min_order(index[DESC], index[ASC]));
}

int	ft_simulate_b_to_a(t_stack *stack_a, t_stack *stack_b)
{
	t_double_list	*last;
	t_double_list	*head;
	int				index[2];

	last = ft_find_last(stack_a->head_stack);
	index[0] = 0;
	head = stack_a->head_stack;
	if (ft_head_is_null(head) || ft_head_is_null(stack_b->head_stack))
		return (2);
	while (stack_b->head_stack->element > head->element)
	{
		index[ASC]++;
		head = head->next;
	}
	head = stack_a->head_stack;
	index[1] = 0;
	while (stack_b->head_stack->element > head->element)
	{
		if (index[DESC]++ == 0)
		{
			head = last;
			continue ;
		}
		head = last->prev;
	}
	return (return_min_order(index[DESC], index[ASC]));
}

int	ft_simulate_shortest_path(t_stack *stack_first, t_stack *stack_second)
{
	if (stack_first->str_id[0] == STACK_A[0])
		return (ft_simulate_b_to_a(stack_first, stack_second));
	return (ft_simulate_a_to_b(stack_second, stack_first));
}

char	*ft_set_operation(int diff, int size, double half, int order)
{
	char	*op;

	if (diff == size - 1)
	{
		op = R_OP;
		if (order == DESC)
			op = RR_OP;
	}
	else if (diff <= half)
		op = R_OP;
	else
		op = RR_OP;
	return (op);
}

int	ft_set_moves(int diff, int size, double half)
{
	int	moves;

	if (diff == size - 1)
		moves = 1;
	else if (diff <= half)
		moves = diff;
	else
		moves = size - diff;
	return(moves);
}

t_op_moves	ft_pick_smallest_rotate(t_stack *stack, int element, int index_to)
{
	t_op_moves	op_moves;
	int			index_from[2];
	int			diff;
	double		half;

	op_moves.moves = 0;
	index_from[0] = ft_get_index(stack, element);
	half = (double)stack->size / 2.0;
	index_from[1] = ASC;
	if (index_from[0] <= index_to)
		diff = index_to - index_from[0];
	else
	{
		index_from[1] = DESC;
		diff = index_from[0] - index_to;
	}
	op_moves.op = P_OP;
	if (diff == 0)
		return (op_moves);
	op_moves.op = ft_set_operation(diff, stack->size, half, index_from[1]);
	op_moves.moves = ft_set_moves(diff, stack->size, half);
	return (op_moves);
}


void	ft_small_sort(t_stack *stack, t_list **operations)
{
	if (stack->size == 2)
			ft_sort_two(stack, operations);
	if (stack->size == 3)
	{
		if (stack->str_id[0] == STACK_A[0])
			ft_sort_three(stack, operations);
		else
			ft_sort_three_desc(stack, operations);
	}
}

void	ft_send_back_sorted_to_a(t_stack *stack_first,
			t_stack *stack_second, t_list **operations)
{
	while (ft_stack_is_empty(stack_second) == FALSE)
		call_double_operation(stack_second, stack_first, operations, P_OP);
}

int	ft_check_sorted_and_send_to_a(t_stack *stack_first,
			t_stack *stack_second, t_list **operations)
{
	if (ft_is_sorted(stack_second->head_stack, DESC) 
		&& ft_is_sorted(stack_first->head_stack, ASC))
	{
		ft_send_back_sorted_to_a(stack_first, stack_second, operations);
		return (TRUE);
	}
	return (FALSE);
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

void	ft_send_half_to_b(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second, int is_first_half)
{
	t_list	**operations;
	int		b_size_adder;
	int		starting_size;

	operations = &push_swap->operations.operations_main;
	b_size_adder = ft_count_elements_below(stack_first, push_swap->median);
	starting_size = stack_second->size;
	while (stack_second->size < (starting_size + b_size_adder))
	{
		ft_less_operations_for_next_below_median(push_swap, stack_first,
			stack_second, push_swap->median);
		if (is_first_half && 
			stack_second->head_stack->element < push_swap->first_quarter)
			call_single_operation(stack_second, operations, R_OP);
	}
}

int	ft_count_of_chuncks(double size)
{
	int		index;

	index = 0;
	while (size > 3)
	{
		index++;
		size /= 2.0;
	}
	return (index);
}

int	ft_swap_rotate_chunks(t_push_swap *push_swap,
			t_stack *stack, int count_of_chunks)
{
	int		qty_of_moves;
	t_list	**operations;
	int		count_of_rotations;

	operations = &push_swap->operations.operations_main;
	qty_of_moves = push_swap->chunks[count_of_chunks].qty_elements - 1;
	count_of_rotations = 0;
	while (stack->head_stack->element < 
		stack->head_stack->next->element && qty_of_moves > 0)
	{
		if (qty_of_moves == 1)
		{
			call_single_operation(stack, operations, S_OP);
			qty_of_moves--;
			continue;
		}
		call_single_operation(stack, operations, S_OP);
		call_single_operation(stack, operations, R_OP);
		count_of_rotations++;
		qty_of_moves--;
	}
	return (count_of_rotations);
}

void	ft_sort_chunks(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int		count_of_chunks;
	int		count_of_rotations;
 	t_list	**operations;

	count_of_chunks = push_swap->count_of_chunks - 1;
	operations = &push_swap->operations.operations_main;
	while (count_of_chunks >= 0)
	{
		count_of_rotations = ft_swap_rotate_chunks(push_swap, stack_second, count_of_chunks);
		while (count_of_rotations)
		{
			call_single_operation(stack_second, operations, RR_OP);
			count_of_rotations--;
		}
		if (ft_is_sorted_up_to_index(stack_second->head_stack,
			push_swap->chunks[count_of_chunks].qty_elements - 1, DESC))
		{
			while (push_swap->chunks[count_of_chunks].qty_elements--)
				call_double_operation(stack_second, stack_first, operations, P_OP);
			count_of_chunks--;
		}
	} 
}

void	ft_send_chunks_to_b(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{
	int			count_of_chuncks;
	int			index;
	int			starting_size;

	starting_size = stack_second->size;
	index = 1;
	count_of_chuncks = push_swap->count_of_chunks;
	while (index < count_of_chuncks)
	{
		push_swap->chunks[index].id = index;
		push_swap->median = ft_find_median(push_swap, stack_first, FALSE);
		ft_send_half_to_b(push_swap, stack_first, stack_second, FALSE);
		push_swap->chunks[index].qty_elements = stack_second->size - starting_size;
		starting_size = stack_second->size;
		index++;
	}
}

void	ft_sort_small_chunks(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second, int is_first_half)
{
		t_list	**operations;
		
		operations = &push_swap->operations.operations_main;
		push_swap->count_of_chunks = ft_count_of_chuncks(stack_first->size);
		push_swap->chunks = (t_chunks *)malloc(sizeof(t_chunks) * 
			push_swap->count_of_chunks);
		push_swap->chunks[0].id = 0;
		ft_send_half_to_b(push_swap, stack_first, stack_second, is_first_half);
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
		ft_sort_chunks(push_swap, stack_first, stack_second);
}


void	ft_sort_four(t_push_swap *push_swap, t_stack *stack_first,
			t_stack *stack_second)
{

	t_list	**operations;

	operations = &push_swap->operations.operations_main;
 	ft_put_element_at_top(push_swap, stack_first, stack_first->min);
	if (ft_is_sorted(stack_first->head_stack, ASC) == TRUE)
			return ;
	call_double_operation(stack_first, stack_second, operations, P_OP);
	ft_sort_three(stack_first, operations);
	call_double_operation(stack_second, stack_first, operations, P_OP);
}


void	ft_sort_three_desc(t_stack *stack, t_list **operations)
{
	int	element_head;
	int	element_next;

	element_head = stack->head_stack->element;
	element_next = stack->head_stack->next->element;
	if (element_head == stack->min && element_next != stack->max)
	{
		call_single_operation(stack, operations, R_OP);
		call_single_operation(stack, operations, S_OP);
	}
	else if (element_head == stack->min && element_next == stack->max)
		call_single_operation(stack, operations, R_OP);
	else if (element_head != stack->min && element_next == stack->min)
		call_single_operation(stack, operations, RR_OP);
	else if (element_head != stack->max && element_next == stack->max)
		call_single_operation(stack, operations, S_OP);
	else if (element_head == stack->max && element_next == stack->min)
	{
		call_single_operation(stack, operations, S_OP);
		call_single_operation(stack, operations, R_OP);
	}
}


void	ft_sort_three(t_stack *stack, t_list **operations)
{
	int	element_head;
	int	element_next;

	element_head = stack->head_stack->element;
	element_next = stack->head_stack->next->element;
	if (element_head == stack->min && element_next == stack->max)
	{
		call_single_operation(stack, operations, RR_OP);
		call_single_operation(stack, operations, S_OP);
	}
	else if (element_head != stack->max && element_next == stack->min)
		call_single_operation(stack, operations, S_OP);
	else if (element_head != stack->min && element_next == stack->max)
		call_single_operation(stack, operations, RR_OP);
	else if (element_head == stack->max && element_next == stack->min)
		call_single_operation(stack, operations, R_OP);
	else if (element_head == stack->max && element_next != stack->min)
	{
		call_single_operation(stack, operations, R_OP);
		call_single_operation(stack, operations, S_OP);
	}
}


void	ft_sort_two(t_stack *stack, t_list **operations)
{
	if (ft_head_is_null(stack->head_stack)
		|| ft_is_single_node(stack->head_stack))
		return ;
	if (stack->str_id[0] == STACK_B[0])
	{
		if (stack->head_stack->element < stack->head_stack->next->element)
			call_single_operation(stack, operations, S_OP);
		return ;
	}
	if (stack->head_stack->element > stack->head_stack->next->element)
			call_single_operation(stack, operations, S_OP);

}


void	ft_set_stacks(t_push_swap *push_swap, t_stack	**stack_first,
			t_stack **stack_second, char *a_or_b)
{
	if (a_or_b[0] == STACK_A[0])
	{
		(*stack_first) = &push_swap->stack_a;
		(*stack_second) = &push_swap->stack_b;
	}
	else
	{
		(*stack_first) = &push_swap->stack_b;
		(*stack_second) = &push_swap->stack_a;
	}
}

void	ft_sort_small(t_push_swap *push_swap, char *a_or_b)
{
	t_stack	*stack_first;
	t_stack	*stack_second;

	ft_set_stacks(push_swap, &stack_first, &stack_second, a_or_b);
	if (push_swap->stack_a.size == 1)
		return ;
	if (push_swap->stack_a.size == 2)
		ft_sort_two(stack_first, &push_swap->operations.operations_main);
	else if (push_swap->stack_a.size == 3)
		ft_sort_three(stack_first, &push_swap->operations.operations_main);
	else if (push_swap->stack_a.size == 4)
		ft_sort_four(push_swap, stack_first, stack_second);
	else
		ft_sort_small_chunks(push_swap, stack_first, stack_second, TRUE);
}