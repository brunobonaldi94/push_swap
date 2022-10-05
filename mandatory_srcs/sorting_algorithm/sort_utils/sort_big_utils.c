/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:12:36 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:25:33 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_find_position(t_stack *stack, int element_index)
{
	t_double_list	*head;
	int				pos;
	int				current_index;
	int				past_index;

	head = stack->head;
	current_index = 0;
	past_index = INT_MAX;
	while (head)
	{
		if (head->index > element_index && head->index < past_index)
		{
			pos = current_index;
			past_index = head->index;
		}
		current_index++;
		head = head->next;
	}
	if (past_index != INT_MAX)
		return (pos);
	return (ft_get_index(stack, stack->max) + 1);
}

t_algo	ft_get_moves(t_stack *stack_a, t_stack *stack_b, int element_index,
		int current_pos)
{
	int				moves_a;
	t_algo			algo;

	moves_a = ft_find_position(stack_a, element_index);
	if (moves_a > stack_a->size / 2)
		moves_a = moves_a - stack_a->size;
	if (current_pos > stack_b->size / 2)
		current_pos = current_pos - stack_b->size;
	algo.moves_a = moves_a;
	algo.moves_b = current_pos;
	return (algo);
}

void	ft_save_less_moves(t_algo *algo, t_algo new_algo)
{
	long int	algo_one_sum;
	long int	algo_two_sum;

	algo_one_sum = ft_abs_number(algo->moves_a)
		+ ft_abs_number(algo->moves_b);
	algo_two_sum = ft_abs_number(new_algo.moves_a)
		+ ft_abs_number(new_algo.moves_b);
	if (algo_one_sum > algo_two_sum)
	{
		algo->moves_a = new_algo.moves_a;
		algo->moves_b = new_algo.moves_b;
	}
}

void	ft_apply_best_move_a(t_stack *stack_a, t_stack *stack_b,
			t_list	**operations)
{
	while (stack_b->algo.moves_a != 0)
	{
		if (stack_b->algo.moves_a < 0 && stack_b->algo.moves_b < 0)
		{
			ft_call_double_operation(stack_a, stack_b, operations, RR_OP);
			stack_b->algo.moves_a++;
			stack_b->algo.moves_b++;
		}
		else if (stack_b->algo.moves_a > 0 && stack_b->algo.moves_b > 0)
		{
			ft_call_double_operation(stack_a, stack_b, operations, R_OP);
			stack_b->algo.moves_a--;
			stack_b->algo.moves_b--;
		}
		if (stack_b->algo.moves_a < 0)
		{
			ft_call_single_operation(stack_a, operations, RR_OP);
			stack_b->algo.moves_a++;
		}
		else if (stack_b->algo.moves_a > 0)
		{
			ft_call_single_operation(stack_a, operations, R_OP);
			stack_b->algo.moves_a--;
		}		
	}
}

void	ft_apply_best_move_b(t_stack *stack_b, t_list **operations)
{
	while (stack_b->algo.moves_b != 0)
	{
		if (stack_b->algo.moves_b < 0)
		{
			ft_call_single_operation(stack_b, operations, RR_OP);
			stack_b->algo.moves_b++;
		}
		else
		{
			ft_call_single_operation(stack_b, operations, R_OP);
			stack_b->algo.moves_b--;
		}
	}
}
