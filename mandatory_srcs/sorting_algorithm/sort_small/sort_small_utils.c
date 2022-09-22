/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:04:11 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/22 00:02:32 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_simulate_moves_up_from_b_to_a(t_list **operations_up, int position_to, int size)
{
	char	*operation;

	if (position_to == 0)
	{
		ft_addback_operation(operations_up, ft_strdup(P_OP));
		return ;
	}
	else if (position_to == size - 1)
	{
		ft_addback_operation(operations_up, ft_strdup(R_OP));
		ft_addback_operation(operations_up, ft_strdup(P_OP));
		return ;
	}
	else if (position_to < (double)size / 2.0)
		operation = ft_strdup(R_OP);
	else
		operation = ft_strdup(RR_OP);
	while (position_to)
	{
		ft_addback_operation(operations_up, operation);
		position_to--;
	}
	ft_addback_operation(operations_up, ft_strdup(P_OP));
}

void	ft_simulate_moves_down_from_b_to_a(t_list **operations_up, int position_to, int size)
{
	char	*operation;

	if (position_to == 0)
	{
		ft_addback_operation(operations_up, ft_strdup(P_OP));
		ft_addback_operation(operations_up, ft_strdup(S_OP));
		return ;
	}
	else if (position_to == size - 1)
	{
		ft_addback_operation(operations_up, ft_strdup(P_OP));
		ft_addback_operation(operations_up, ft_strdup(R_OP));
		return ;
	}
	else if (position_to < (double)size / 2.0)
		operation = ft_strdup(R_OP);
	else
		operation = ft_strdup(RR_OP);
	while (position_to)
	{
		ft_addback_operation(operations_up, operation);
		position_to--;
	}
	ft_addback_operation(operations_up, ft_strdup(S_OP));
}

int ft_pick_less_moves(t_list *op1, t_list *op2)
{
	int op1_len;
	int op2_len;
	
	op1_len = ft_lstsize(op1);
	op2_len = ft_lstsize(op2);
	if (op2_len > op1_len)
		return(SECONDARY_OP);
	return (TERTIARY_OP);
}

int ft_calculate_less_amount_moves(t_push_swap *push_swap,
		t_stack *from_stack, t_stack *to_stack)
{
	int				position_to;
	int				position_down;
	int				index_from;
	ft_lstclear(&push_swap->operations.operations_secondary, &free);
	ft_lstclear(&push_swap->operations.operations_tertiary, &free);
	push_swap->operations.operations_secondary = NULL;
	push_swap->operations.operations_tertiary = NULL;
	if (from_stack->str_id[0] == STACK_B[0])
	{
		// if (from_stack->head_stack->index == 0)
		// {
		// 	to_stack->op_moves = ft_pick_smallest_rotate(to_stack,
		// 	to_stack->min, 0);
		// 	while (to_stack->op_moves.moves)
		// 	{
		// 		ft_addback_operation(&push_swap->operations.operations_secondary,
		// 		ft_strdup(to_stack->op_moves.op));
		// 		to_stack->op_moves.moves--;
		// 	}
		// 	ft_addback_operation(&push_swap->operations.operations_secondary,ft_strdup(P_OP));
		// 	return (SECONDARY_OP);
		// }
		index_from = from_stack->head_stack->index;
		position_to = ft_get_index_from_next_index(to_stack, index_from, ASC);
		ft_simulate_moves_up_from_b_to_a(
			&push_swap->operations.operations_secondary,
			position_to, to_stack->size);
		position_down = ft_get_index_from_previous_index(to_stack, index_from, ASC);
		ft_simulate_moves_down_from_b_to_a(
			&push_swap->operations.operations_tertiary,
			position_down, to_stack->size);
	}
	ft_print_operations(push_swap->operations.operations_secondary);
	ft_printf("------------------\n");
	ft_print_operations(push_swap->operations.operations_tertiary);
 	return (ft_pick_less_moves(push_swap->operations.operations_secondary, 
			push_swap->operations.operations_tertiary));
}

void	ft_apply_calculated_moves(t_push_swap *push_swap,
		t_stack *stack_first, t_stack *stack_second, t_list *operations)
{
	char	*operation;
	t_list	**operations_main;

	operations_main = &push_swap->operations.operations_main;
	if (stack_first->str_id[0] == STACK_A[0])
	{
		while (operations)
		{
			operation = (char *)operations->content;
			if (ft_check_operation(operation, S_OP)
				|| ft_check_operation(operation, R_OP)
				|| ft_check_operation(operation, RR_OP)
			)
			{
				call_single_operation(stack_first, operations_main, operation);
			}
			if (ft_check_operation(operation, P_OP))
				call_double_operation(stack_second, stack_first,
					operations_main, operation);
			operations = operations->next;
		}
	}
}