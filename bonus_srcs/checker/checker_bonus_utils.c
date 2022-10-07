/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:39:22 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 23:26:40 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_apply_operations_and_print(t_push_swap *push_swap)
{
	int	is_sorted;
	int	is_b_empty;

	is_sorted = FALSE;
	ft_apply_operations(push_swap, push_swap->operations.checker);
	is_sorted = ft_is_sorted(push_swap->stack_a.head, ASC);
	is_b_empty = ft_stack_is_empty(&push_swap->stack_b) == TRUE;
	ft_print_result(is_sorted && is_b_empty);
}
