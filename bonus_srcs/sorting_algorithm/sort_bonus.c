/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:19:48 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_sort(t_push_swap *push_swap)
{
	ft_sort_aux_list(push_swap, &push_swap->stack_a, TRUE);
	if (push_swap->is_sorted == TRUE)
		return ;
	if (push_swap->stack_a.size <= 4)
		ft_sort_small(push_swap);
	else
		ft_sort_big(push_swap);
}
