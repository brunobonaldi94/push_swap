/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:29:44 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/18 18:26:11 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap_stack(t_stack *stack)
{
	t_double_list	*temp;

	temp = stack->head_stack->next;
	stack->head_stack->next = temp->next;
	stack->head_stack->prev = temp;
	temp->next = stack->head_stack;
	temp->prev = NULL;
	if (stack->head_stack->next != NULL)
		stack->head_stack->next->prev = stack->head_stack;
	stack->head_stack = temp;
}

int	ft_swap_stack_sab(t_stack *stack)
{
	if (ft_head_is_null(stack->head_stack)
		|| ft_is_single_node(stack->head_stack))
		return (FALSE);
	ft_swap_stack(stack);
	return (TRUE);
}

int	ft_swap_stack_ss(t_stack *stack_a, t_stack *stack_b)
{
	int	first_rotate_return;
	int	second_rotate_return;

	first_rotate_return = ft_swap_stack_sab(stack_a);
	second_rotate_return = ft_swap_stack_sab(stack_b);
	return (first_rotate_return || second_rotate_return);
}
