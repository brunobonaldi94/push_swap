/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:26:04 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/22 22:54:08 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_result(int is_sorted)
{
	if (is_sorted)
	{
		ft_printf(GREEN);
		ft_printf("%s\n","[OK]");
		ft_printf(RESET);
	}
	else
	{
		ft_printf(RED);
		ft_printf("%s\n","[KO]");
		ft_printf(RESET);
	}
}

void	ft_print_stack(t_stack stack, char A_or_B)
{
	t_double_list	*last;
	int				index;
	int				is_sorted;

	ft_printf(GREEN);
	ft_printf("===============================\n");
	ft_printf("stack: %c\nsize is: %d\nmin: %d\nmax: %d\n", A_or_B, stack.size,
	stack.min, stack.max);
	ft_printf("===============================\n");
	ft_printf(RESET);
	last = NULL;
	index = 0;
	is_sorted = TRUE;
	while (stack.head_stack)
	{
		ft_printf("[%d]: %d\n",index, stack.head_stack->element);
		if (!stack.head_stack->next)
			last = stack.head_stack;
		if (stack.head_stack->next && stack.head_stack->element > stack.head_stack->next->element)
			is_sorted = FALSE;
		stack.head_stack = stack.head_stack->next;
		index++;
	}
	ft_printf("-------------------------------\n", last);
	print_result(is_sorted);
	// while (last)
	// {
	// 	index--;
	// 	ft_printf("[%d]: %d\n",index, last->element);
	// 	last = last->prev;
	// }
}

void	ft_print_all_stack(t_push_swap *push_swap)
{
	ft_print_stack(push_swap->stack_a, 'A');
	ft_print_stack(push_swap->stack_b, 'B');
}

t_double_list	*ft_create_node(int element)
{
	t_double_list	*new_node;

	new_node = (t_double_list *)malloc(sizeof(t_double_list));
	new_node->element = element;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_clear_stack(t_stack *stack)
{
	if (ft_head_is_null(stack->head_stack))
		return ;
	while (stack->head_stack)
		ft_pop_stack_free(stack);
	stack->head_stack = NULL;
}

void	ft_clear_all_stack(t_push_swap *push_swap)
{
	ft_clear_stack(&push_swap->stack_a);
	ft_clear_stack(&push_swap->stack_b);
	ft_clear_stack(&push_swap->stack_aux);
}

void	init_min_max(t_stack *stack, int element)
{
	stack->min = element;
	stack->max = element;
}

void	set_min_max(t_stack *stack, int element)
{
	if (stack->min > element)
		stack->min = element;
	if (stack->max < element)
		stack->max = element;
}

int	ft_populate_stack(t_push_swap *push_swap)
{
	int				argv_to_int;
	int				index;
	t_double_list	*new_node;
	t_double_list	*head;
 
	index = 0;
	push_swap->is_valid = parse_args(push_swap);
	push_swap->is_sorted = TRUE;
	head = push_swap->args_list.head_stack;
	while (head && push_swap->is_valid)
	{
		argv_to_int = (head->element);
		new_node = ft_create_node(argv_to_int);
		set_min_max(&push_swap->stack_a, argv_to_int);
		ft_push_stack(&push_swap->stack_a, new_node);
		index++;
		if (head->next && argv_to_int < head->next->element)
			push_swap->is_sorted = FALSE;
		head = head->next;
		
	}
	push_swap->global_min = push_swap->stack_a.min;
	push_swap->global_max = push_swap->stack_a.max;
	ft_clear_stack(&push_swap->args_list);
	return (push_swap->is_valid);
}
