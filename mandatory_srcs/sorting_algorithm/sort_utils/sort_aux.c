/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:23 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 22:59:52 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_fill_aux_list(t_stack *stack_aux, t_double_list *last_a)
{
	t_double_list	*new_node;

	while (last_a)
	{
		new_node = ft_create_node(last_a->element);
		ft_push_stack(stack_aux, new_node);
		last_a = last_a->prev;
	}
}

void	ft_fill_aux_indexes(t_stack *stack_aux, t_stack *stack_a)
{
	t_double_list	*head;
	t_double_list	*head_a;
	int				index;

	head = stack_aux->head;
	index = 0;
	while (head)
	{
		head->index = index++;
		head = head->next;
	}
	head = stack_aux->head;
	head_a = stack_a->head;
	while (head_a)
	{
		head = stack_aux->head;
		while (head)
		{
			if (head_a->element == head->element)
				head_a->index = head->index;
			head = head->next;
		}
		head_a = head_a->next;
	}
}

void	ft_sort_aux_list(t_push_swap *push_swap,
			t_stack *stack, int fill_index)
{
	t_double_list	*last;
	t_double_list	*last_aux;

	if (push_swap->stack_aux.head != NULL)
		ft_clear_stack(&push_swap->stack_aux);
	last = ft_find_last(stack->head);
	ft_fill_aux_list(&push_swap->stack_aux, last);
	last_aux = ft_find_last(push_swap->stack_aux.head);
	ft_quick_sort_recursive(push_swap->stack_aux.head, last_aux);
	if (fill_index == TRUE)
		ft_fill_aux_indexes(&push_swap->stack_aux, stack);
}
