/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:19:58 by kationg           #+#    #+#             */
/*   Updated: 2025/06/23 16:14:31 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

void error_mssg(char *mssg)
{
	ft_putstr_fd(mssg, 1);
	exit(1);
}

void load_stack_a_F(char **argv, int size, t_stack *stack)
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
		free(d_arr[i++]);
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




//count the length to allocate for token d_array and also check for invalid arguments(char etc)
int count_numbers(char **argv)
{
	char **subarr;
	int len = 0;
	int i;
	while (*argv)
	{
		i = 0;
		subarr = ft_split(*argv, ' ');
		while (subarr[i])
		{
			if (not_digit(subarr))
			{
				free_2d_arr(subarr);
				error_mssg("\nError\nOnly accepts numbers as argument");
			}
			len++;
			i++;
		}
		free_2d_arr(subarr);
		argv++;
	}
	return(len);
}


//where i first parse the input by splitting the argv if i has multiple digits then adding to res one by one
int *parse_input(char **argv)
{
	int i = 0;
	int j;
	int len = 0;
	char **subarr;
	int *res;

	res = ft_calloc(sizeof(int *), count_numbers(argv));
	while (argv[i])
	{
		j = 0;
		subarr = ft_split(argv[i], ' ');
		while (subarr[j])
		{
			res[len] = ft_atoi(subarr[j]);
			len++;
			j++;
		}
		free_2d_arr(subarr);
		i++;
	}
	return(res);
}

void check_duplicates(int *arr)
{
	int i = 0;
	int j;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (arr[i] == arr[j])
			{
				error_mssg("Error\nDuplicate numbers found");
				exit(1);
			}
			j++;
		}
		i++;
	}
}


t_node *create_node(int *num)
{
	t_node *ptr;
	
	ptr = malloc(sizeof(t_node));
	ptr->value = *num;
	ptr->next = NULL;
	ptr->prev = NULL;
	return (ptr);
}

void load_stack_a(int *tokens, t_stack *stack_a)
{
	t_node *prev;
	t_node *new;
	while (*tokens)
	{
		new = create_node(tokens);
		if (!stack_a->head)
			stack_a->head = new;
		else 
		{
			prev->next = new;
			new->prev = prev;
		}
		prev = new;
		tokens++;
		stack_a->size++;
	}
}

int main(int argc, char *argv[])
{
	t_stack stack_a;
	int *tokens;

	ft_memset(&stack_a, 0, sizeof(stack_a));
	if (argc < 2)
		error_mssg("please enter at least one number");
	tokens = parse_input(++argv);
	check_duplicates(tokens);
	/*
	for (int i = 0; i < 10; i++)
	{
		ft_printf("%i ", tokens[i]);
	}*/
	load_stack_a(tokens, &stack_a);
	t_node *ptr = stack_a.head;
	
	while (ptr)
	{
		ft_printf("%i ", ptr->value);
		ptr = ptr->next;
	}


}
