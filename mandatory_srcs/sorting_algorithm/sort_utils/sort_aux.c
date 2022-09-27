/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:23 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/26 19:44:52 by bbonaldi         ###   ########.fr       */
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

	head = stack_aux->head_stack;
	index = 0;
	while (head)
	{
		head->index = index++;
		head = head->next;
	}
	head = stack_aux->head_stack;
	head_a = stack_a->head_stack;
	while (head_a)
	{
		head = stack_aux->head_stack;
		while (head)
		{
			if (head_a->element == head->element)
				head_a->index = head->index;
			head = head->next;
		}
		head_a = head_a->next;
	}
}

void	ft_sort_aux_list_chunks(t_push_swap *push_swap, t_stack *stack,
			int elements_count)
{
	t_double_list	*last_up_to_index;
	t_double_list	*last_aux;

	if (push_swap->stack_aux.head_stack != NULL)
		ft_clear_stack(&push_swap->stack_aux);
	last_up_to_index = ft_find_up_to_index(stack->head_stack, elements_count);
	ft_fill_aux_list(&push_swap->stack_aux, last_up_to_index);
	last_aux = ft_find_last(push_swap->stack_aux.head_stack);
	ft_quick_sort_recursive(push_swap->stack_aux.head_stack, last_aux);
}

void	ft_sort_aux_list(t_push_swap *push_swap,
			t_stack *stack, int fill_index)
{
	t_double_list	*last;
	t_double_list	*last_aux;

	if (push_swap->stack_aux.head_stack != NULL)
		ft_clear_stack(&push_swap->stack_aux);
	last = ft_find_last(stack->head_stack);
	ft_fill_aux_list(&push_swap->stack_aux, last);
	last_aux = ft_find_last(push_swap->stack_aux.head_stack);
	ft_quick_sort_recursive(push_swap->stack_aux.head_stack, last_aux);
	if (fill_index == TRUE)
		ft_fill_aux_indexes(&push_swap->stack_aux, stack);
}