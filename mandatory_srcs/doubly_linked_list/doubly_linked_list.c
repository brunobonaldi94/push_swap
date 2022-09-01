/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:26:04 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/01 05:09:41 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_list_forwards(t_stack stack, char A_or_B)
{
	t_double_list	*last;
	ft_printf(GREEN);
	ft_printf("===============================\n");
	ft_printf("stack: %c\nsize is: %d\n", A_or_B, stack.size);
	ft_printf("===============================\n");
	ft_printf(RESET);
	last = NULL;
	while (stack.head_stack)
	{
		ft_printf("element: %d\n", stack.head_stack->element);
		if (!stack.head_stack->next)
			last = stack.head_stack;
		stack.head_stack = stack.head_stack->next;
	}
	ft_printf("-------------------------------\n");
	while (last)
	{
		ft_printf("element: %d\n", last->element);
		last = last->prev;
	}
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

void	ft_clear_stack(t_double_list **head, int *size)
{
	t_double_list	*pop_list_return;

	pop_list_return = NULL;
	if (ft_check_head_nulish(head))
		return ;
	while ((*head))
	{
		pop_list_return = ft_pop_stack(head, size);
		free(pop_list_return);
		pop_list_return = NULL;
	}
	head = NULL;
	
}

void	ft_populate_stack(t_push_swap *push_swap)
{
	t_double_list	*new_node;
	int				argv_to_int;
	int				last_index;

	push_swap->stack_a.head_stack = NULL;
	push_swap->stack_b.head_stack = ft_create_node(10);
	push_swap->stack_b.size++;
	last_index = push_swap->argc - 1;
	while (last_index >= 1)
	{
		argv_to_int = ft_atoi(push_swap->argv[last_index]);
		new_node = ft_create_node(argv_to_int);
		ft_push_stack(&push_swap->stack_a.head_stack, new_node,
			&push_swap->stack_a.size);
		last_index--;
	}
	ft_pop_push_stack_pab(&push_swap->stack_a.head_stack, &push_swap->stack_b.head_stack, 
	 	&push_swap->stack_a.size, &push_swap->stack_b.size);
	// ft_pop_push_stack_pab(&push_swap->head_stack_a, &push_swap->head_stack_b);
	// ft_swap_stack_ss(&push_swap->head_stack_a, &push_swap->head_stack_b);
	// ft_pop_push_stack_pab(&push_swap->head_stack_a, &push_swap->head_stack_b);
	ft_rotate_stack_rr(&push_swap->stack_a.head_stack, &push_swap->stack_b.head_stack);
	print_list_forwards(push_swap->stack_a, 'A');
	print_list_forwards(push_swap->stack_b, 'B');
	ft_clear_stack(&push_swap->stack_a.head_stack, &push_swap->stack_a.size);
	ft_clear_stack(&push_swap->stack_b.head_stack, &push_swap->stack_a.size);
}
