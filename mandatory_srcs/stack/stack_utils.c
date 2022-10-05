/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:24:15 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:21:48 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	ft_set_min_max(t_stack *stack, int element)
{
	if (stack->min > element)
		stack->min = element;
	if (stack->max < element)
		stack->max = element;
}
