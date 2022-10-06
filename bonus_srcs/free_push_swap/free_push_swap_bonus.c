/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_push_swap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:51:42 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 00:46:10 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_clear_operations(t_push_swap *push_swap)
{
	ft_lstclear(&push_swap->operations.main, free);
	ft_lstclear(&push_swap->operations.checker, free);
}

void	ft_clear_stack(t_stack *stack)
{
	if (ft_head_is_null(stack->head))
		return ;
	while (stack->head)
		ft_pop_stack_free(stack);
	stack->head = NULL;
}

void	ft_clear_all_stack(t_push_swap *push_swap)
{
	ft_clear_stack(&push_swap->args_list);
	ft_clear_stack(&push_swap->stack_aux);
	ft_clear_stack(&push_swap->stack_a);
	ft_clear_stack(&push_swap->stack_b);
}

int	ft_print_error(t_push_swap *push_swap)
{
	ft_printf(RED);
	write(2, ERROR, ft_strlen(ERROR));
	ft_printf(RESET);
	ft_clear_push_swap(push_swap);
	return (ERROR_CODE);
}

void	ft_clear_push_swap(t_push_swap *push_swap)
{
	ft_clear_all_stack(push_swap);
	ft_clear_operations(push_swap);
}
