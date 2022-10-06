/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:39:22 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 00:45:58 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

char	*ft_copy_until_character(char *line, char c)
{
	char	*line_no_nl;
	size_t	index;
	size_t	line_len;

	if (line == NULL || !*line)
		return (NULL);
	line_len = 0;
	index = 0;
	while (line[line_len] && line[line_len] != c)
		line_len++;
	line_no_nl = (char *)malloc((line_len + 1) * sizeof(char));
	while (index < line_len)
	{
		line_no_nl[index] = line[index];
		index++;
	}
	line_no_nl[index] = '\0';
	return (line_no_nl);
}

void	ft_apply_operations(t_push_swap *push, t_list *list)
{
	while (list)
	{
		if (ft_strncmp((char *)list->content, RA, 3) == 0)
			ft_rotate_stack_rab(&push->stack_a);
		else if (ft_strncmp((char *)list->content, RB, 3) == 0)
			ft_rotate_stack_rab(&push->stack_b);
		else if (ft_strncmp((char *)list->content, RR, 3) == 0)
			ft_rotate_stack_rr(&push->stack_a, &push->stack_b);
		else if (ft_strncmp((char *)list->content, SA, 3) == 0)
			ft_swap_stack_sab(&push->stack_a);
		else if (ft_strncmp((char *)list->content, SB, 3) == 0)
			ft_swap_stack_sab(&push->stack_b);
		else if (ft_strncmp((char *)list->content, SS, 3) == 0)
			ft_swap_stack_ss(&push->stack_a, &push->stack_b);
		else if (ft_strncmp((char *)list->content, PA, 3) == 0)
			ft_pop_push_stack_pab(&push->stack_b, &push->stack_a);
		else if (ft_strncmp((char *)list->content, PB, 3) == 0)
			ft_pop_push_stack_pab(&push->stack_a, &push->stack_b);
		else if (ft_strncmp((char *)list->content, RRA, 3) == 0)
			ft_rotate_stack_rrab(&push->stack_a);
		else if (ft_strncmp((char *)list->content, RRB, 3) == 0)
			ft_rotate_stack_rrab(&push->stack_b);
		else if (ft_strncmp((char *)list->content, RRR, 3)== 0)
			ft_rotate_stack_rrr(&push->stack_a, &push->stack_b);
		list = list->next;
	}
}

void	ft_checker_bonus(t_push_swap *push_swap)
{
	char	*line;
	char	*line_no_nl;
	t_list	**operations;
	int		is_sorted;

	operations = &push_swap->operations.checker;
	line = NULL;
	while (TRUE)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		line_no_nl = ft_copy_until_character(line, NEW_LINE);
		free(line);
		ft_addback_operation(operations, line_no_nl);
	}
	ft_apply_operations(push_swap, *operations);
	is_sorted = ft_is_sorted(push_swap->stack_a.head, ASC) 
		&& ft_stack_is_empty(&push_swap->stack_b) == TRUE;
	ft_print_result(is_sorted);
	return ;
}
