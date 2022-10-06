/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:58:36 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 00:46:41 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_put_element_at_top(t_push_swap *push_swap,
			t_stack *stack, int element)
{
	int		index_element;
	t_list	**operations;

	operations = &push_swap->operations.main;
	index_element = ft_get_index(stack, element);
	if (index_element == 1)
	{
		ft_call_single_operation(stack, operations, S_OP);
		return ;
	}
	if (index_element == stack->size - 1)
	{
		ft_call_single_operation(stack, operations, RR_OP);
		return ;
	}
	if (index_element <= stack->size / 2)
	{
		while (stack->head->element != element)
			ft_call_single_operation(stack, operations, R_OP);
		return ;
	}
	while (stack->head->element != element)
		ft_call_single_operation(stack, operations, RR_OP);
}

int	ft_get_index(t_stack *stack, int element)
{
	t_double_list	*head;
	int				index;

	head = stack->head;
	index = 0;
	while (head)
	{
		if (head->element == element)
			break ;
		head = head->next;
		index++;
	}
	if (index > stack->size)
		return (-1);
	return (index);
}

void	ft_find_min_max(t_stack *stack)
{
	t_double_list	*head;

	head = stack->head;
	stack->max = INT_MIN;
	stack->min = INT_MAX;
	while (head)
	{
		ft_set_min_max(stack, head->element);
		head = head->next;
	}
}

int	ft_is_sorted(t_double_list *head_stack, int order)
{
	int				is_sorted;
	t_double_list	*head;
	t_double_list	*next;

	is_sorted = TRUE;
	head = head_stack;
	if (head == NULL)
		return (is_sorted);
	next = head->next;
	while (next)
	{	
		if (order == ASC && head->element > next->element)
			return (FALSE);
		if (order == DESC && head->element < next->element)
			return (FALSE);
		head = head->next;
		next = head->next;
	}
	return (is_sorted);
}
