/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:12:02 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/03 22:43:16 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	merge(int arr[], int left, int mid, int right)
{
	int	i;
	int	j;
	int	k;
	int n1;
	int n2;
	int *left_arr;
	int	*right_arr;

	n1 = mid - left + 1;
	n2 = right - mid; 
	left_arr = (int *)malloc(sizeof(int) * n1);
	right_arr = (int *)malloc(sizeof(int) * n2);
	i = 0;
	while (i < n1)
	{
		left_arr[i] = arr[left + i];
		i++;
	}
	j = 0;
	while (j < n2)
	{
		right_arr[j] = arr[mid + 1 + j];
		j++;
	}
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2)
	{
		if (left_arr[i] <= right_arr[j])
		{
			arr[k] = left_arr[i];
			i++;
		}
		else
		{
			arr[k] = right_arr[j];
			j++;
		}
		k++;
	}

	 while (i < n1) 
	 {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
  
    while (j < n2) 
	{
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right)
{
	if (left < right) 
	{
		int mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}