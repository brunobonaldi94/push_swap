/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:26:04 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:22:25 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

t_double_list	*ft_create_node(int element)
{
	t_double_list	*new_node;

	new_node = (t_double_list *)malloc(sizeof(t_double_list));
	new_node->element = element;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	ft_populate_stack(t_push_swap *push_swap)
{
	int				argv_to_int;
	int				index;
	t_double_list	*new_node;
	t_double_list	*head;

	index = 0;
	push_swap->is_valid = ft_parse_args(push_swap);
	push_swap->is_sorted = TRUE;
	head = push_swap->args_list.head;
	while (head && push_swap->is_valid)
	{
		argv_to_int = (head->element);
		new_node = ft_create_node(argv_to_int);
		ft_set_min_max(&push_swap->stack_a, argv_to_int);
		ft_push_stack(&push_swap->stack_a, new_node);
		index++;
		if (head->next && argv_to_int < head->next->element)
			push_swap->is_sorted = FALSE;
		head = head->next;
	}
	return (push_swap->is_valid);
}
