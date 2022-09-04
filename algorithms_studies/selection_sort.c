/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:42:29 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/03 18:25:26 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	selection_sort(int arr[], int n)
{
	int	i;
	int	j;
	int	min_index;

	i = 0;
	while(i < n)
	{
		min_index = i;
		j = i + 1;
		while (j < n)
		{
			if (arr[j] < arr[min_index])
				min_index = j;
			j++;
		} 
		if (min_index != i)
			swap(&arr[min_index], &arr[i]);
		i++;
	}
}