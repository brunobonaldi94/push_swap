/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:27:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/04 23:22:25 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_compare_atoi_with_itoa_failed(int atoi_result, char *argv_atoi)
{	
	char	*itoa_result;
	size_t	argv_atoi_len;
	int		has_failed;

	argv_atoi_len = ft_strlen(argv_atoi);
	itoa_result = ft_itoa(atoi_result);
	has_failed = FALSE;
	if (ft_strncmp(itoa_result, argv_atoi, argv_atoi_len) != 0)
		has_failed = TRUE;
	free(itoa_result);
	return (has_failed);
}

int	has_unique_args(t_push_swap *push_swap)
{
	t_double_list	*head;
	t_double_list	*helper;

	if (push_swap->args_list.size == 0)
		return (FALSE);
	head = push_swap->args_list.head;
	while (head)
	{
		helper = head->next;
		while (helper)
		{
			if (head->element == helper->element)
				return (FALSE);
			helper = helper->next;
		}
		head = head->next;
	}
	return (TRUE);
}

int	split_args(t_push_swap *push_swap, int index_argv)
{
	char					**split_argv;
	int						split_index;
	t_double_list			*new;
	int						argv_to_int;

	if (!*push_swap->argv[index_argv])
		return (FALSE);
	split_argv = ft_split(push_swap->argv[index_argv], ' ');
	split_index = 0;
	while (split_argv[split_index])
	{
		argv_to_int = ft_atoi(split_argv[split_index]);
		if (ft_compare_atoi_with_itoa_failed(argv_to_int,
				split_argv[split_index]))
			return (FALSE);
		new = ft_create_node(argv_to_int);
		ft_push_stack(&push_swap->args_list, new);
		free(split_argv[split_index]);
		split_index++;
	}
	free(split_argv);
	split_argv = NULL;
	return (TRUE);
}

int	ft_parse_args(t_push_swap *push_swap)
{
	int	index_argv;
	int	has_parsed_succeeded;

	index_argv = 1;
	has_parsed_succeeded = TRUE;
	while (index_argv < push_swap->argc)
	{
		has_parsed_succeeded = split_args(push_swap, index_argv);
		if (has_parsed_succeeded == FALSE)
			return (has_parsed_succeeded);
		index_argv++;
	}
	has_parsed_succeeded = has_unique_args(push_swap);
	return (has_parsed_succeeded);
}
