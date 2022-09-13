/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:47:48 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/13 02:28:47 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	swap(int *i, int *j)
{
	int	swap;

	swap = *i;
	*i = *j;
	*j = swap;
}


void	print_arr(int arr[], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i == n -1)
		{
			printf("%d\n", arr[i]);
			break;
		}
		printf("%d,", arr[i]);
		i++;
	}
}

int	main(void)
{
	int arr[] = {64,23,4,5,100,8};
	int n = sizeof(arr) / sizeof(arr[0]);
	print_arr(arr, n);
	insertion_sort(arr, n);
	printf("sorted arr\n");
	print_arr(arr, n);
}