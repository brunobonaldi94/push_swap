/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:39:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/26 21:50:44 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_operation(char *operation_called, char *operation_check)
{
	int	are_equal;

	are_equal = 
		ft_strncmp(operation_called, operation_check, MAX_OPERATION_LEN);
	return (are_equal == 0);
}

void	call_single_operation(t_stack *stack,
			t_list **operation, char *operation_start)
{
	char	*new_operation;
	int		operation_result;

	if (ft_check_operation(operation_start, S_OP))
		operation_result = ft_swap_stack_sab(stack);
	else if (ft_check_operation(operation_start, R_OP))
		operation_result = ft_rotate_stack_rab(stack);
	else if (ft_check_operation(operation_start, RR_OP))
		operation_result = ft_rotate_stack_rrab(stack);
	if (operation_result == TRUE)
	{
		new_operation = ft_strjoin(operation_start, stack->str_id);
		ft_addback_operation(operation, new_operation);
	}
}

void	call_double_operation(t_stack *stack_first, t_stack *stack_second,
			t_list **operation, char *operation_start)
{
	char	*new_operation;
	int		operation_result;

	if (ft_check_operation(operation_start, P_OP))
		operation_result = ft_pop_push_stack_pab(stack_first, stack_second);
	else if (ft_check_operation(operation_start, R_OP))
		operation_result = ft_rotate_stack_rr(stack_first, stack_second);
	else if (ft_check_operation(operation_start, RR_OP))
		operation_result = ft_rotate_stack_rrr(stack_first, stack_second);
	else if (ft_check_operation(operation_start, S_OP))
		operation_result = ft_swap_stack_ss(stack_first, stack_second);
	if (operation_result == TRUE)
	{
		if (ft_check_operation(operation_start, P_OP))
		{
			new_operation = ft_strjoin(operation_start, stack_second->str_id);
			ft_find_min_max(stack_first);
			ft_find_min_max(stack_second);
		}
		else if (ft_check_operation(operation_start, R_OP) 
			|| ft_check_operation(operation_start, RR_OP))
			new_operation = ft_strjoin(operation_start, "r");
		else
			new_operation = ft_strjoin(operation_start, "s");
		ft_addback_operation(operation, new_operation);
	}
}
