/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:29:44 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 00:46:22 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_push_stack(t_stack *stack, t_double_list *new)
{
	if (!stack || new == NULL)
		return ;
	new->next = stack->head;
	new->prev = NULL;
	if (stack->head)
		(stack->head)->prev = new;
	(stack->head) = new;
	stack->size += 1;
}

void	ft_pop_stack_free(t_stack *stack)
{
	t_double_list	*temp;

	if (ft_head_is_null(stack->head))
		return ;
	temp = stack->head->next;
	free(stack->head);
	stack->head = temp;
	if (stack->head)
		stack->head->prev = NULL;
	stack->size -= 1;
}

t_double_list	*ft_pop_stack_move_pointer(t_stack *stack)
{
	t_double_list	*temp;

	if (ft_head_is_null(stack->head))
		return (NULL);
	if (ft_is_single_node(stack->head))
	{
		temp = stack->head;
		stack->head = NULL;
		stack->size -= 1;
		return (temp);
	}
	stack->head = stack->head->next;
	temp = stack->head->prev;
	if (stack->head)
		stack->head->prev = NULL;
	stack->size -= 1;
	return (temp);
}

int	ft_pop_push_stack_pab(t_stack *stack_first, t_stack *stack_second)
{
	t_double_list	*pop_list_item;

	if (ft_head_is_null(stack_first->head))
		return (FALSE);
	pop_list_item = ft_pop_stack_move_pointer(stack_first);
	if (pop_list_item == NULL)
		return (FALSE);
	ft_push_stack(stack_second, pop_list_item);
	return (TRUE);
}
