/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:27:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/16 00:24:24 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_int_min_max(long int atoi_result)
{
	return (atoi_result < INT_MIN || atoi_result > INT_MAX);
}

int ft_compare_atoi_failed(int atoi_result, char *argv_atoi)
{	
	char	*itoa_result;
	size_t	argv_atoi_len;

	argv_atoi_len = ft_strlen(argv_atoi);
	itoa_result = ft_itoa(atoi_result);
	if (ft_strncmp(itoa_result, argv_atoi, argv_atoi_len) != 0)
	{
		free(itoa_result);
		return (TRUE);
	}
	return (FALSE);
}

int	has_atoi_failed(int atoi_result, char *argv_atoi)
{
	size_t	argv_atoi_len;
	size_t	index;

	index = 0;
	while (*argv_atoi)
	{
		if(!ft_isdigit(*argv_atoi))
			return (TRUE);
		argv_atoi++;
		index++;
	}
	argv_atoi_len = ft_strlen(argv_atoi);
	if (atoi_result == 0
		&& ft_strncmp(argv_atoi, "0", argv_atoi_len) != 0)
		return (TRUE);
	return (FALSE);
}

int	has_unique_args(t_push_swap *push_swap)
{
	t_double_list	*head;
	t_double_list	*helper;

	if (push_swap->args_list.size == 0)
		return (FALSE);
	head = push_swap->args_list.head_stack;
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
  		if (ft_compare_atoi_failed(argv_to_int, split_argv[split_index]) 
			|| has_atoi_failed(argv_to_int, split_argv[split_index]))
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

int	parse_args(t_push_swap *push_swap)
{
	int	index_argv;
	int	has_parsed_suceeded;

	index_argv = 1;
	has_parsed_suceeded = TRUE;
	while (index_argv < push_swap->argc)
	{
		has_parsed_suceeded = split_args(push_swap, index_argv);
		if (has_parsed_suceeded == FALSE)
			return (has_parsed_suceeded);
		index_argv++;
	}
	has_parsed_suceeded = has_unique_args(push_swap);
	return (has_parsed_suceeded);
}
