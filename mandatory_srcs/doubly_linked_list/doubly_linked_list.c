/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:26:04 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/08/30 04:24:08 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_list_forwards(t_double_list *head)
{
	while (head)
	{
		ft_printf("element: %d\n", head->element);
		head = head->next;
	}
}

void	print_list_backwards(t_double_list *head)
{
	while (head->next)
		head = head->next;
	while (head)
	{
		ft_printf("element: %d\n", head->element);
		head = head->prev;
	}
}


t_double_list	*ft_create_node(int element)
{
	t_double_list	*new_node;

	new_node = (t_double_list *)malloc(sizeof(t_double_list));
	new_node->element = element;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_push_stack(t_double_list **head, t_double_list *new)
{
	if (head == NULL || new == NULL)
		return ;
	new->next = *head;
	new->prev = NULL;
	if ((*head))
		(*head)->prev = new;
	(*head) = new;
}

void	ft_pop_stack(t_double_list **head)
{
	t_double_list	*temp;

	if (head == NULL)
		return ;
	temp = (*head)->next;
	free((*head));
	*head = temp;
	if ((*head))
		(*head)->prev = NULL;
}

void	ft_clear_stack(t_double_list **head)
{
	if (head == NULL)
		return ;
	while ((*head))
	{
		ft_pop_stack(head);
	}
	head = NULL;
}

void	populate_stack(t_push_swap *push_swap)
{
	t_double_list	*new_node;
	int				argv_to_int;
	int				last_index;

	push_swap->head_stack = NULL;
	last_index = push_swap->argc - 1;
	while (last_index >= 1)
	{
		argv_to_int = ft_atoi(push_swap->argv[last_index]);
		new_node = ft_create_node(argv_to_int);
		ft_push_stack(&push_swap->head_stack, new_node);
		last_index--;
	}
	print_list_forwards(push_swap->head_stack);
	ft_printf("-------------------------------\n");
	print_list_backwards(push_swap->head_stack);
	ft_clear_stack(&push_swap->head_stack);
}
