/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:19:58 by kationg           #+#    #+#             */
/*   Updated: 2025/06/09 12:06:54 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

void error_mssg(char *mssg)
{
	ft_printf("%s", mssg);
	exit(1);
}

void load_stack_a(char **argv, int size, t_stack *stack)
{
	size -= 1;
	int i = 0;
	int j = 0;
	t_node *ptr_curr;
	t_node *ptr_prev;
	ptr_curr = stack->head;
	while (i < size)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				error_mssg("Program only accepts numbers as input");
		}
		ptr_curr = malloc(sizeof(t_node));
		ptr_curr->value = ft_atoi(argv[i]);
		ptr_prev = ptr_curr;
		if (i + 1 == size)
		{
			ptr_curr->next = stack->head;
			ptr_curr->prev = ptr_prev;
		}
		else 
		{
			ptr_curr = ptr_curr->next;
			if (ptr_prev)
				ptr_curr->prev = ptr_prev;
		}
		stack->size++;
	}
}

void free_2d_arr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		free(arr[i]);
	}
	free(arr);
}


char **parse_input(char **argv)
{
	int i = 0;
	int j;
	char **subarr;
	char **res;
	while (argv[i])
	{
		j = 0;
		subarr = ft_split(argv[i], ' ');
		while (subarr[j])
		{
			res[i] = subarr[j];
			j++;
		}
		i++;
		free_2d_arr(subarr);
	}
	return(res);
}


int main(int argc, char *argv[])
{
	t_stack stack_a;
	char **tokens;

	if (argc < 2)
		error_mssg("please enter at least one number");
	tokens = parse_input(argv);
	load_stack_a(argv, argc, &stack_a);
}
