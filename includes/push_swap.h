/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:17:58 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/08/30 03:16:43 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include "libft.h"
# include "stdlib.h"

# define TRUE 1
# define FALSE 0

# define ERROR_CODE 1
# define SUCCESS_CODE 0
# define ERROR_CODE_FUNCTION -1

typedef	struct s_double_list
{
	int						element;
	struct s_double_list*	prev;
	struct s_double_list*	next;
}	t_double_list;

typedef	struct s_push_swap
{
	t_double_list	*head_stack;
	int				argc;
	char			**argv;
}	t_push_swap;

void	populate_stack(t_push_swap *push_swap);

#endif //PUSH_SWAP_H