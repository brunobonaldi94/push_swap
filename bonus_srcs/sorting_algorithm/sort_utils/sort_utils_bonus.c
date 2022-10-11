/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:58:36 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/10 21:00:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

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
