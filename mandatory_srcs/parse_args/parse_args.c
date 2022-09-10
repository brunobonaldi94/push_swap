/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:27:34 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/10 21:49:13 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	parse_args(t_push_swap *push_swap)
{
 	t_list	*new;
	int		is_valid_args;
	int		argv_to_int;
	int		last_index;

	last_index = push_swap->argc - 2;
	push_swap->args_list = NULL;
	is_valid_args = TRUE;
	while (last_index >= 1)
	{
		argv_to_int = ft_atoi(push_swap->argv[last_index]);
		if (argv_to_int == 0 && push_swap->argv[last_index][0] != '0')
			return (FALSE);
		new = ft_lstnew(&argv_to_int);
		ft_lstadd_back(&push_swap->args_list, new);
		last_index--;
	}
	return (is_valid_args);
}