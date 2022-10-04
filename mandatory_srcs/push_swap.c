/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:16:57 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 19:56:51 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	load_argc_argv(t_push_swap *push_swap, int argc, char *argv[])
{
	push_swap->argc = argc;
	push_swap->argv = argv;
}

int	ft_initialize_push_swap(t_push_swap *push_swap, int argc, char *argv[])
{
	load_argc_argv(push_swap, argc, argv);
	ft_initialize_stack(&push_swap->stack_a, STACK_A);
	ft_initialize_stack(&push_swap->stack_b, STACK_B);
	ft_initialize_stack(&push_swap->args_list, STACK_ARGS);
	ft_initialize_stack(&push_swap->stack_aux, STACK_AUX);
	ft_initialize_operations(push_swap);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_push_swap	push_swap;

	ft_initialize_push_swap(&push_swap, argc, argv);
	ft_populate_stack(&push_swap);
	if (push_swap.is_valid == FALSE)
	{
		ft_printf("Error\n");
		return (ERROR_CODE);
	}
	ft_sort(&push_swap);
	return (SUCCESS_CODE);
}