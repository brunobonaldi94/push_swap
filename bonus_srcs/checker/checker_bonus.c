/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:39:22 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/06 23:22:57 by bbonaldi         ###   ########.fr       */
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

int	ft_is_valid_operation(char *op)
{
	if (ft_strncmp(op, RA, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, RB, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, RR, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, SA, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, SB, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, SS, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, PA, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, PB, OPERATION_LEN) == 0)
		return (TRUE);
	else if (ft_strncmp(op, RRA, OPERATION_LEN + 1) == 0)
		return (TRUE);
	else if (ft_strncmp(op, RRB, OPERATION_LEN + 1) == 0)
		return (TRUE);
	else if (ft_strncmp(op, RRR, OPERATION_LEN + 1) == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_apply_operation(t_push_swap *push_swap, t_list *list)
{
	if (ft_strncmp((char *)list->content, RA, OPERATION_LEN) == 0)
		ft_rotate_stack_rab(&push_swap->stack_a);
	else if (ft_strncmp((char *)list->content, RB, OPERATION_LEN) == 0)
		ft_rotate_stack_rab(&push_swap->stack_b);
	else if (ft_strncmp((char *)list->content, RR, OPERATION_LEN) == 0)
		ft_rotate_stack_rr(&push_swap->stack_a, &push_swap->stack_b);
	else if (ft_strncmp((char *)list->content, SA, OPERATION_LEN) == 0)
		ft_swap_stack_sab(&push_swap->stack_a);
	else if (ft_strncmp((char *)list->content, SB, OPERATION_LEN) == 0)
		ft_swap_stack_sab(&push_swap->stack_b);
	else if (ft_strncmp((char *)list->content, SS, OPERATION_LEN) == 0)
		ft_swap_stack_ss(&push_swap->stack_a, &push_swap->stack_b);
	else if (ft_strncmp((char *)list->content, PA, OPERATION_LEN) == 0)
		ft_pop_push_stack_pab(&push_swap->stack_b, &push_swap->stack_a);
	else if (ft_strncmp((char *)list->content, PB, OPERATION_LEN) == 0)
		ft_pop_push_stack_pab(&push_swap->stack_a, &push_swap->stack_b);
	else if (ft_strncmp((char *)list->content, RRA, OPERATION_LEN + 1) == 0)
		ft_rotate_stack_rrab(&push_swap->stack_a);
	else if (ft_strncmp((char *)list->content, RRB, OPERATION_LEN + 1) == 0)
		ft_rotate_stack_rrab(&push_swap->stack_b);
	else if (ft_strncmp((char *)list->content, RRR, OPERATION_LEN + 1) == 0)
		ft_rotate_stack_rrr(&push_swap->stack_a, &push_swap->stack_b);
	else
		return (FALSE);
	return (TRUE);
}

int	ft_apply_operations(t_push_swap *push_swap, t_list *list)
{
	int	valid_commands;

	valid_commands = TRUE;
	while (list)
	{
		valid_commands = ft_apply_operation(push_swap, list);
		if (valid_commands == FALSE)
			break ;
		list = list->next;
	}
	return (valid_commands);
}

void	ft_checker_bonus(t_push_swap *push_swap)
{
	char	*line;
	char	*line_no_nl;
	int		valid_commands;

	line = NULL;
	while (TRUE)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		line_no_nl = ft_copy_until_character(line, NEW_LINE);
		free(line);
		valid_commands = ft_is_valid_operation(line_no_nl);
		if (valid_commands == FALSE)
		{
			free(line_no_nl);
			ft_print_error(push_swap);
			return ;
		}
		ft_addback_operation(&push_swap->operations.checker, line_no_nl);
	}
	ft_apply_operations_and_print(push_swap);
}
