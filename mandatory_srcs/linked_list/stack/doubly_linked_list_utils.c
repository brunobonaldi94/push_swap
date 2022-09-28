/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:24:15 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/27 20:50:13 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_initialize_stack(t_stack *stack, char *str_id)
{
	stack->head_stack = NULL;
	stack->size = 0;
	stack->min = INT_MAX;
	stack->max = INT_MIN;
	stack->str_id = str_id;
	stack->count_of_chunks = -1;
	stack->inner_chunks.median = NULL;
	stack->inner_chunks.qty_elements = NULL;
}

int	ft_head_is_null(t_double_list *head)
{
	return (head == NULL);
}

int	ft_is_single_node(t_double_list *head)
{
	if (head->next == NULL && head->prev == NULL)
		return (TRUE);
	return (FALSE);
}
