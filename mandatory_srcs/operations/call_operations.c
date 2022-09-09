/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:39:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/09 22:28:14 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_operation(char *operation_called, char *operation_check)
{
	int	are_equal;

	are_equal = ft_strncmp(operation_called, operation_check,
					MAX_OPERATION_LEN);
	return (are_equal == 0);
}

void	call_single_operation(t_stack *stack, char *operation)
{
	ft_printf("%s\n", operation);
	if (check_operation(operation, SA) || check_operation(operation,SB))
		ft_swap_stack_sab(stack);
	else if(check_operation(operation, RA) || check_operation(operation, RB))
		ft_rotate_stack_rab(stack);
	else if(check_operation(operation, RRA) || check_operation(operation, RRB))
		ft_rotate_stack_rrab(stack);
}

void	call_double_operation(t_stack *stack_first, t_stack *stack_second,
			char *operation)
{
	ft_printf("%s\n", operation);
	if (check_operation(operation, PA) || check_operation(operation,PB))
		ft_pop_push_stack_pab(stack_first, stack_second);
	else if(check_operation(operation, RR))
		ft_rotate_stack_rr(stack_first, stack_second);
	else if(check_operation(operation, RRR))
		ft_rotate_stack_rrr(stack_first, stack_second);
}