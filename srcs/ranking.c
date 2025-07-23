/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:34:43 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 03:10:30 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap_val(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// once everything is sorted only then swap the i with pivot 
// as the last step then return the pivot pivot_index
//fixed bug where i end it right before the pivot index
int	partition(int *array, int first, int last)
{
	int	pivot;
	int	i;
	int	j;

	pivot = array[last];
	i = first - 1;
	j = first;
	while (j < last)
	{
		if (array[j] < pivot)
		{
			i++;
			swap_val(&array[i], &array[j]);
		}
		j++;
	}
	swap_val(&array[i + 1], &array[last]);
	return (i + 1);
}

void	ranking(int *array, t_stack *stack, int num_count)
{
	int		rank;
	int		i;
	t_node	*ptr;

	ptr = stack->head;
	while (ptr)
	{
		rank = 0;
		i = 0;
		while (i < num_count)
		{
			if (ptr->value == array[i])
				ptr->rank = rank;
			i++;
			rank++;
		}
		ptr = ptr->next;
	}
}

void	quick_sort(int *array, int low, int high)
{
	int	pivot_index;

	if (low < high)
	{
		pivot_index = partition(array, low, high);
		quick_sort(array, low, pivot_index - 1);
		quick_sort(array, pivot_index + 1, high);
	}
}
