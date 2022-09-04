/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:20:41 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/04 20:42:56 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int partition_low (int arr[], int low, int high) 
{ 
    int pivot; // pivot 
    int i;
	int j;

	pivot = arr[low];
	i = low;
	j = low + 1;
	while (j <= high)
	{
		if (arr[j] < pivot)
        { 
            i++;
            swap(&arr[i], &arr[j]);
        } 
		j++;
	}
	swap(&arr[i], &arr[low]);
    return (i);
}

int partition_high (int arr[], int low, int high) 
{ 
    int pivot; // pivot 
    int i;
	int j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j <= high - 1)
	{
		if (arr[j] < pivot)
        { 
            i++;
            swap(&arr[i], &arr[j]);
        } 
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
    return (i + 1);
} 

  
void quick_sort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        
        int pi = partition_low(arr, low, high); 
        quick_sort(arr, low, pi - 1); 
        quick_sort(arr, pi + 1, high); 
    } 
}