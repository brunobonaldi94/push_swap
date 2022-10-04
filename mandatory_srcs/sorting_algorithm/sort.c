/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 19:58:45 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort(t_push_swap *push_swap)
{
	ft_sort_aux_list(push_swap, &push_swap->stack_a, TRUE);
	if (push_swap->is_sorted == TRUE)
		return ;
	if (push_swap->stack_a.size <= 4)
		ft_sort_small(push_swap);
	else
		ft_sort_big(push_swap);
	ft_print_operations(push_swap->operations.operations_main);
	ft_print_all_stack(push_swap);
	ft_clear_all_stack(push_swap);
	ft_clear_operations(push_swap);
}