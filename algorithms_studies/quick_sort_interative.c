/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_interative.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:20:41 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/05 03:45:28 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int partition_high (int arr[], int low, int high) 
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

void	copy_arr(int *arr2, int *arr, int size)
{
	int i = 0;

 	while (i < size)
	{
		arr2[i] = arr[i];
		i++;
	}
}
  
void quick_sort_interative(int arr[], int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];
	int size = h + 1;
	int arr2[6] = {0};
    // initialize top of stack
    int top = -1;
 
    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

 	copy_arr(arr2, arr, size);
    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];
 
        // Set pivot element at its correct position
        // in sorted array
        int p = partition_high(arr, l, h);
 		copy_arr(arr2, arr, size);
        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }
 
        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}