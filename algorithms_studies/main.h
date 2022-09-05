/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:47:57 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/09/05 03:09:03 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "stdio.h"
# include "stdlib.h"
# include "libft.h"

void	selection_sort(int arr[], int n);
void	bubble_sort(int arr[], int n);
void	swap(int *i, int *j);
void	insertion_sort(int arr[], int n);
void	heap_sort(int arr[], int n);
void	quick_sort(int arr[], int low, int high);
void 	quick_sort_interative(int arr[], int l, int h);
void	merge_sort(int arr[], int left, int right);
void	radix_sort(int array[], int size);
#endif