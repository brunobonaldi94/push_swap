/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:52:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/28 22:26:52 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_big(t_push_swap *push_swap)
{
	ft_sort_big_chunks(push_swap, &push_swap->stack_a, &push_swap->stack_b);
	return ;
}