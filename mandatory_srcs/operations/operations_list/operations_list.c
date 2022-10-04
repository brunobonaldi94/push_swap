/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:49:17 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 19:58:15 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_initialize_operations(t_push_swap *push_swap)
{
	push_swap->operations.operations_main = NULL;
}

void	ft_addback_operation(t_list **operations,
			char *operation_string)
{
	t_list	*new_operation;

	new_operation = ft_lstnew(operation_string);
	ft_lstadd_back(operations, new_operation);
}

void	ft_print_operations(t_list *operations)
{
	t_list	*head;

	head = operations;
	while (head)
	{
		ft_printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

void	ft_clear_operations(t_push_swap *push_swap)
{
	ft_lstclear(&push_swap->operations.operations_main, free);
}