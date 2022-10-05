/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:16:57 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:19:27 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_push_swap	push_swap;

	if (argc <= 1)
		return (ERROR_CODE);
	ft_initialize_push_swap(&push_swap, argc, argv);
	ft_populate_stack(&push_swap);
	if (push_swap.is_valid == FALSE)
		return (ft_print_error());
	ft_sort(&push_swap);
	ft_print_operations(push_swap.operations.main);
	ft_clear_push_swap(&push_swap);
	return (SUCCESS_CODE);
}
