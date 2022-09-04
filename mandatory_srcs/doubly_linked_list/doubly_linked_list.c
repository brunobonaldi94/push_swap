/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:26:04 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/04 21:07:47 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_print_stack(t_stack stack, char A_or_B)
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

void	ft_clear_stack(t_double_list **head, int *size)
{
	if (ft_check_head_nulish(head))
		return ;
	while ((*head))
		ft_pop_stack_free(head, size);
	head = NULL;
}

void	ft_clear_all_stack(t_push_swap *push_swap)
{
	ft_clear_stack(&push_swap->stack_a.head_stack, &push_swap->stack_a.size);
	ft_clear_stack(&push_swap->stack_b.head_stack, &push_swap->stack_a.size);
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
		ft_push_stack(&push_swap->stack_a.head_stack, new_node,
			&push_swap->stack_a.size);
		last_index--;
	}
}
