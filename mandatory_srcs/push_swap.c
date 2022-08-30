/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:16:57 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/08/30 04:15:58 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	load_argc_argv(t_push_swap *push_swap, int argc, char *argv[])
{
	push_swap->argc = argc;
	push_swap->argv = argv;
}

int	initialize_push_swap(t_push_swap *push_swap, int argc, char *argv[])
{
	load_argc_argv(push_swap, argc, argv);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_push_swap	push_swap;

	initialize_push_swap(&push_swap, argc, argv);
	populate_stack(&push_swap);
	return (SUCCESS_CODE);
}