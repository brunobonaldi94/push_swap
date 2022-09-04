/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:58:26 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/03 19:06:10 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void heapify(int arr[], int n, int i)
{
	int largest;
	int left;
	int right;

	largest = i;
	left = 2 * i + 1;
	right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;
	if (right < n && arr[right] > arr[largest])
		largest = right;
	if (largest != i)
	{
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

void	heap_sort(int arr[], int n)
{
	int	i;

	i = n / 2 - 1;
	while (i >= 0)
	{
		heapify(arr, n, i);
		i--;		
	}
	i = n - 1;
	while (i >= 0)
	{
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
		i--;
	}
}