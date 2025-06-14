/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:19:58 by kationg           #+#    #+#             */
/*   Updated: 2025/06/09 15:24:45 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

void error_mssg(char *mssg)
{
	ft_putstr_fd(mssg, 2);
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

void free_2d_arr(char **d_arr)
{
	int i = 0;
	while (d_arr[i])
	{
		free(d_arr[i]);
	}
	free(d_arr);
}

int not_digit(char **d_arr)
{
	int i = 0;
	int j = 0;
	while(d_arr[i])
	{
		while (d_arr[i][j])
		{
			if (!ft_isdigit(d_arr[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

//count the length to allocate for token d_array
int count_numbers(char **argv)
{
	char **subarr;
	int len = 0;
	while (*argv)
	{
		subarr = ft_split(*argv, ' ');
		while (*subarr)
		{
			if (not_digit(subarr))
			{
				free_2d_arr(subarr);
				error_mssg("Error\nOnly accepts numbers as argument");
			}
			len++;
			subarr++;
		}
		free_2d_arr(subarr);
		argv++;
	}
	return(len);
}


//where i first parse the input by splitting the argv if i has multiple digits then adding to res one by one
char **parse_input(char **argv)
{
	int i = 0;
	int j;
	char **subarr;
	char **res;
	res = ft_calloc(sizeof(char *), count_numbers(argv));
	while (argv[i])
	{
		j = 0;
		subarr = ft_split(argv[i], ' ');
		while (subarr[j])
		{
			res[i] = subarr[j];
			i++;
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

	ft_memset(&stack_a, 0, sizeof(stack_a));
	if (argc < 2)
		error_mssg("please enter at least one number");
	tokens = parse_input(argv);
	load_stack_a(tokens, argc, &stack_a);

}
