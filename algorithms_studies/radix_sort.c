/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 22:44:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/04 20:42:43 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_max(int array[], int n)
{
	int max = array[0];

	int i = 1;
	while (i < n)
	{
		if (array[i] > max)
			max = array[i];
		i++;
	}
	return max;
}

void	counting_sort(int array[], int size, int place) 
{
	int output[size + 1];
	int max = (array[0] / place) % 10;
	int i = 1;

	while (i < size)
	{
		if (((array[i] / place) % 10) > max)
			 max = array[i];
		i++;
	}

	int count[max + 1];

	i = 0;
	while (i < max)
	{
		count[i] = 0;
		i++;
	}

	i = 0;
	while (i < size)
	{
		count[(array[i] / place) % 10]++;
		i ++;
	}

	i = 1;
	while (i < 10)
	{
		count[i] += count[i - 1];
		i++;
	}

	i = size -1;
	while (i >= 0)
	{
		output[count[(array[i] / place) % 10] - 1] = array[i];
		count[(array[i] / place) % 10]--;
		i--;
	}

	i = 0;
	while (i < size)
	{
		array[i] = output[i];
		i++;
	}
}

void radix_sort(int array[], int size)
{
	int max;
	int place;

	place = 1;
	max = get_max(array, size);
	while (max / place > 0)
	{
		counting_sort(array, size, place);
		place *= 10;
	}
}

 