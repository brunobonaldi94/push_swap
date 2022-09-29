/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:01:31 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/28 23:18:54 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	{	if (order == ASC && head->element > next->element)
			return (FALSE);
		if (order == DESC && head->element < next->element)
			return (FALSE);
		head = head->next;
		next = head->next;
	}
	return (is_sorted);
}

int	ft_is_sorted_up_to_index(t_double_list *head_stack, int index, int order)
{
	int				is_sorted;
	t_double_list	*head;
	t_double_list	*next;

	is_sorted = TRUE;
	head = head_stack;
	if (head == NULL)
		return (is_sorted);
	next = head->next;
	while (next && index)
	{	if (order == ASC && head->element > next->element)
			return (FALSE);
		if (order == DESC && head->element < next->element)
			return (FALSE);
		head = head->next;
		next = head->next;
		index--;
	}
	return (is_sorted);
}

void	ft_apply_steps(t_push_swap *push, t_list *list)
{
	t_list	*l;

	l = list;
	while (l)
	{
		if (ft_strncmp((char *)l->content, "ra", 3) == 0)
			ft_rotate_stack_rab(&push->stack_aux2);
		else if (ft_strncmp((char *)l->content, "rb", 3) == 0)
			ft_rotate_stack_rab(&push->stack_b);
		else if (ft_strncmp((char *)l->content, "rr", 3) == 0)
			ft_rotate_stack_rr(&push->stack_aux2, &push->stack_b);
		else if (ft_strncmp((char *)l->content, "sa", 3) == 0)
			ft_swap_stack_sab(&push->stack_aux2);
		else if (ft_strncmp((char *)l->content, "sb", 3) == 0)
			ft_swap_stack_sab(&push->stack_b);
		else if (ft_strncmp((char *)l->content, "ss", 3) == 0)
			ft_swap_stack_ss(&push->stack_aux2, &push->stack_b);
		else if (ft_strncmp((char *)l->content, "pa", 3) == 0)
			ft_pop_push_stack_pab(&push->stack_b, &push->stack_aux2);
		else if (ft_strncmp((char *)l->content, "pb", 3) == 0)
			ft_pop_push_stack_pab(&push->stack_aux2, &push->stack_b);
		else if (ft_strncmp((char *)l->content, "rra", 3) == 0)
			ft_rotate_stack_rrab(&push->stack_aux2);
		else if (ft_strncmp((char *)l->content, "rrb", 3) == 0)
			ft_rotate_stack_rrab(&push->stack_b);
		else if (ft_strncmp((char *)l->content, "rrr", 3)== 0)
			ft_rotate_stack_rrr(&push->stack_aux2, &push->stack_b);
		l = l->next;
	}
}


void	ft_sort(t_push_swap *push_swap)
{
	//ft_print_all_stack(push_swap);
	//ft_fill_aux_list(&push_swap->stack_aux2, ft_find_last(push_swap->stack_a.head_stack));
	//ft_print_stack(&push_swap->stack_aux2);
	push_swap->median = ft_find_median(push_swap, &push_swap->stack_a, TRUE);
	if (push_swap->is_sorted == TRUE)
		return ;
	if (push_swap->stack_a.size <= 100)
		ft_sort_small(push_swap);
	else
		ft_sort_big(push_swap);
	//ft_print_operations(push_swap->operations.operations_main);
	//debug
	//ft_apply_steps(push_swap, push_swap->operations.operations_main);
	//
	//ft_print_all_stack(push_swap);
	//debug
	//ft_print_stack(&push_swap->stack_aux2);
	//
	ft_clear_all_stack(push_swap);
	ft_clear_operations(push_swap);
	ft_clear_chunks(push_swap);
}