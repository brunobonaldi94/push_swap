/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:29:44 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/07 20:38:22 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_stack(t_stack *stack, t_double_list *new)
{
	if (!stack || new == NULL)
		return ;
	new->next = stack->head_stack;
	new->prev = NULL;
	if (stack->head_stack)
		(stack->head_stack)->prev = new;
	(stack->head_stack) = new;
	stack->size += 1;
}

void	ft_pop_stack_free(t_stack *stack)
{
	t_double_list	*temp;

	if (ft_head_is_null(stack->head_stack))
		return ;
	temp = stack->head_stack->next;
	free(stack->head_stack);
	stack->head_stack = temp;
	if (stack->head_stack)
		stack->head_stack->prev = NULL;
	stack->size -= 1;
}

t_double_list	*ft_pop_stack_move_pointer(t_stack *stack)
{
	t_double_list	*temp;

	if (ft_head_is_null(stack->head_stack))
		return (NULL);
	if (ft_is_single_node(stack->head_stack))
	{
		temp = stack->head_stack;
		stack->head_stack = NULL;
		stack->size -= 1;
		return temp;
	}
	stack->head_stack = stack->head_stack->next;
	temp = stack->head_stack->prev;
	if (stack->head_stack)
		stack->head_stack->prev = NULL;
	stack->size -= 1; 
	return (temp);
}

void	ft_pop_push_stack_pab(t_stack *stack_first, t_stack *stack_second)
{
	t_double_list	*pop_list_item;
	if (ft_head_is_null(stack_first->head_stack))
		return ;
	pop_list_item = ft_pop_stack_move_pointer(stack_first);
	if (pop_list_item == NULL) 
		return ;
	ft_push_stack(stack_second, pop_list_item);
}