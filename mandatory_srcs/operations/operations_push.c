/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:29:44 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/04 20:45:02 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_stack(t_double_list **head, t_double_list *new, int *size)
{
	if (ft_has_no_head(head) || new == NULL)
		return ;
	new->next = *head;
	new->prev = NULL;
	if (*head)
		(*head)->prev = new;
	(*head) = new;
	*size += 1;
}

void	ft_pop_stack_free(t_double_list **head, int *size)
{
	t_double_list	*temp;

	if (ft_check_head_nulish(head) )
		return ;
	temp = (*head)->next;
	free(*head);
	*head = temp;
	if (*head)
		(*head)->prev = NULL;
	*size -= 1;
}

t_double_list	*ft_pop_stack_move_pointer(t_double_list **head, int *size)
{
	t_double_list	*temp;

	if (ft_check_head_nulish(head))
		return (NULL);
	if (ft_is_single_node(head))
	{
		temp = (*head);
		(*head) = NULL;
		return temp;
	}
	*head = (*head)->next;
	temp = (*head)->prev;
	if (*head)
		(*head)->prev = NULL;
	*size -= 1; 
	return (temp);
}

void	ft_pop_push_stack_pab(t_double_list **head_first,
			t_double_list **head_second,  int *size_first, int *size_second)
{
	t_double_list	*pop_list_item;
	if (ft_check_head_nulish(head_first))
		return ;
	pop_list_item = ft_pop_stack_move_pointer(head_first, size_first);
	if (pop_list_item == NULL) 
		return ;
	ft_push_stack(head_second, pop_list_item, size_second);
}