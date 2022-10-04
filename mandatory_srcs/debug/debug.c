/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:11:06 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 20:12:41 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_result(int is_sorted)
{
	if (is_sorted)
	{
		ft_printf(GREEN);
		ft_printf("%s\n","[OK]");
		ft_printf(RESET);
	}
	else
	{
		ft_printf(RED);
		ft_printf("%s\n","[KO]");
		ft_printf(RESET);
	}
}

void	ft_print_stack(t_stack *stack)
{
	t_double_list	*last;
	t_double_list	*head;
	int				index;
	int				is_sorted;

	ft_printf(GREEN);
	ft_printf("===============================\n");
	ft_printf("stack: %c\nsize is: %d\nmin: %d\nmax: %d\n", stack->str_id[0] - ('a' - 'A'), stack->size,
	stack->min, stack->max);
	ft_printf("===============================\n");
	ft_printf(RESET);
	last = NULL;
	index = 0;
	is_sorted = TRUE;
	head = stack->head_stack;
	while (head)
	{
		ft_printf("[%d]: %d - index: %d\n",index, head->element, head->index);
		if (!head->next)
			last = head;
		if (head->next && head->element > head->next->element)
			is_sorted = FALSE;
		head = head->next;
		index++;
	}
	ft_printf("-------------------------------\n", last);
	print_result(is_sorted);
}

void	ft_print_all_stack(t_push_swap *push_swap)
{
	ft_print_stack(&push_swap->stack_a);
	ft_print_stack(&push_swap->stack_b);
}
