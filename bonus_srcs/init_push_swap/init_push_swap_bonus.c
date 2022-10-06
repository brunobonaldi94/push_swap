/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_push_swap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:47:12 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 00:46:13 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_initialize_operations(t_push_swap *push_swap)
{
	push_swap->operations.main = NULL;
	push_swap->operations.checker = NULL;
}

void	ft_initialize_stack(t_stack *stack, char *str_id)
{
	stack->head = NULL;
	stack->size = 0;
	stack->min = INT_MAX;
	stack->max = INT_MIN;
	stack->str_id = str_id;
}

void	ft_load_argc_argv(t_push_swap *push_swap, int argc, char *argv[])
{
	push_swap->argc = argc;
	push_swap->argv = argv;
}

int	ft_initialize_push_swap(t_push_swap *push_swap, int argc, char *argv[])
{
	ft_load_argc_argv(push_swap, argc, argv);
	ft_initialize_stack(&push_swap->stack_a, STACK_A);
	ft_initialize_stack(&push_swap->stack_b, STACK_B);
	ft_initialize_stack(&push_swap->args_list, STACK_ARGS);
	ft_initialize_stack(&push_swap->stack_aux, STACK_AUX);
	ft_initialize_operations(push_swap);
	return (TRUE);
}
