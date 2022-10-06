/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_operations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:39:21 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 00:46:16 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	ft_check_operation(char *operation_called, char *operation_check)
{
	int	are_equal;

	are_equal = ft_strncmp(operation_called, operation_check,
			MAX_OPERATION_LEN);
	return (are_equal == 0);
}

void	ft_call_single_operation(t_stack *stack,
			t_list **operation, char *op)
{
	char	*new_operation;
	int		operation_result;

	operation_result = TRUE;
	if (ft_check_operation(op, S_OP))
		operation_result = ft_swap_stack_sab(stack);
	else if (ft_check_operation(op, R_OP))
		operation_result = ft_rotate_stack_rab(stack);
	else if (ft_check_operation(op, RR_OP))
		operation_result = ft_rotate_stack_rrab(stack);
	if (operation_result == FALSE)
		return ;
	new_operation = ft_strjoin(op, stack->str_id);
	ft_addback_operation(operation, new_operation);
}

void	ft_call_double_operation(t_stack *stack_first, t_stack *stack_second,
			t_list **operation, char *op)
{
	char	*new_operation;
	int		operation_result;

	operation_result = TRUE;
	if (ft_check_operation(op, P_OP))
		operation_result = ft_pop_push_stack_pab(stack_first, stack_second);
	else if (ft_check_operation(op, R_OP))
		operation_result = ft_rotate_stack_rr(stack_first, stack_second);
	else if (ft_check_operation(op, RR_OP))
		operation_result = ft_rotate_stack_rrr(stack_first, stack_second);
	else if (ft_check_operation(op, S_OP))
		operation_result = ft_swap_stack_ss(stack_first, stack_second);
	if (operation_result == FALSE)
		return ;
	if (ft_check_operation(op, P_OP))
	{
		new_operation = ft_strjoin(op, stack_second->str_id);
		ft_find_min_max(stack_first);
		ft_find_min_max(stack_second);
	}
	else if (ft_check_operation(op, R_OP) || ft_check_operation(op, RR_OP))
		new_operation = ft_strjoin(op, "r");
	else
		new_operation = ft_strjoin(op, "s");
	ft_addback_operation(operation, new_operation);
}
