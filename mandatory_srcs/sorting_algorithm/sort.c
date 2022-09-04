/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/04 21:41:52 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort(t_push_swap *push_swap)
{
	ft_print_all_stack(push_swap);
	ft_quick_sort(push_swap);
	ft_print_all_stack(push_swap);
	ft_clear_all_stack(push_swap);
}