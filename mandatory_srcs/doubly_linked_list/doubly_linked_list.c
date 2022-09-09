/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:26:04 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/09 23:03:55 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_print_stack(t_stack stack, char A_or_B)
{
	t_double_list	*last;
	int				index;

	ft_printf(GREEN);
	ft_printf("===============================\n");
	ft_printf("stack: %c\nsize is: %d\nmin: %d\nmax: %d\n", A_or_B, stack.size, 
	stack.min, stack.max);
	ft_printf("===============================\n");
	ft_printf(RESET);
	last = NULL;
	index = 0;
	while (stack.head_stack)
	{
		ft_printf("[%d]: %d\n",index, stack.head_stack->element);
		if (!stack.head_stack->next)
			last = stack.head_stack;
		stack.head_stack = stack.head_stack->next;
		index++;
	}
	ft_printf("-------------------------------\n");
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

void	ft_populate_stack(t_push_swap *push_swap)
{
	t_double_list	*new_node;
	int				argv_to_int;
	int				last_index;

	last_index = push_swap->argc - 1;
	while (last_index >= 1)
	{
		argv_to_int = ft_atoi(push_swap->argv[last_index]);
		new_node = ft_create_node(argv_to_int);
		if (last_index == push_swap->argc - 1)
			init_min_max(&push_swap->stack_a, argv_to_int);
		else
			set_min_max(&push_swap->stack_a, argv_to_int);
		ft_push_stack(&push_swap->stack_a, new_node);
		last_index--;
	}
}
