/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:19:58 by kationg           #+#    #+#             */
/*   Updated: 2025/07/20 16:04:18 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"
#include "libft/ft_printf.h"
#include "libft/libft.h"

void error_mssg(char *mssg)
{
	ft_putstr_fd(mssg, 2);
	exit(1);
}
/* this is wrong implementation
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
*/
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
	int j;
	while(d_arr[i])
	{
		j = 0;
		while (d_arr[i][j])
		{
			if (d_arr[i][0] == '-' || d_arr[i][j] == '\0')
				j++;
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
				error_mssg("Error\n");
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
int *parse_input(char **argv, int *num_count)
{
	int i = 0;
	int j;
	int len = 0;
	char **subarr;
	int *res;
	
	*num_count = count_numbers(argv);
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

void check_duplicates(int *arr, int length)
{
	//now i know why zero is breaking my code because the while loop checks for arr[i] null terminator which triggers the zero
	int i = 0;
	int j;
	while (i < length)
	{
		j = i + 1;
		while (j < length)
		{
			if (arr[i] == arr[j])
			{
				error_mssg("Error\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}


t_node *create_node(int num)
{
	t_node *ptr;
	
	ptr = malloc(sizeof(t_node));
	ptr->value = num;
	ptr->next = NULL;
	return (ptr);
}

void load_stack_a(int *tokens, t_stack *stack_a, int length)
{
	t_node *new;
	t_node *ptr;
	int i = 0;

	ptr = stack_a->head;
	while (i < length)
	{
		new = create_node(tokens[i]);
		if (!stack_a->head)
			stack_a->head = new;
		else 
			ptr->next = new;
		ptr = new;
		i++;
		stack_a->size++;
	}
	stack_a->tail = new;
}

void swap_val(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int *array, int first, int last)
{
	int pivot = array[last];
	int i = first - 1;
	int j = first;
	//fixed bug where i end it right before the pivot index
	while (j < last)
	{
		if (array[j] < pivot)
		{
			i++;
			swap_val(&array[i], &array[j]);
		}
		//instead of only progressing j in else which can cause an infinite loop, always increment it
		j++;
	}
	// once everything is sorted only then swap the i with pivot as the last step then return the pivot index
	swap_val(&array[i + 1], &array[last]);
	return (i + 1);
}


void quick_sort(int *array, int low, int high)
{
	if (low < high)
	{
		int pivot_index = partition(array, low, high);
		quick_sort(array, low, pivot_index - 1);
		quick_sort(array, pivot_index + 1, high);
	}
}


void ranking(int *array, t_stack *stack, int num_count)
{
	int rank = 0;
	int i;
	t_node *ptr = stack->head;
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


void swap(t_stack *stack)
{
	t_node *tmp;
	tmp = stack->head;

	stack->head = tmp->next;
	tmp->next = stack->head->next;
	stack->head->next = tmp;
}


void rev_rotate(t_stack *stack)
{
	t_node *tmp;
	t_node *ptr;

	tmp = stack->tail;
	ptr = stack->head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = NULL;
	stack->tail = ptr;
	tmp->next = stack->head;
	stack->head = tmp;
}

void rotate(t_stack *stack)
{
	t_node *tmp;
	tmp = stack->head;

	if (!stack->head || !tmp->next)
		return;
	stack->head = tmp->next;
	tmp->next = NULL;
	stack->tail->next = tmp;
	stack->tail = tmp;
}

void push(t_stack *src, t_stack *dest)
{
    if (!src->head)
        return;

    t_node *tmp = src->head;
    src->head = tmp->next;
    if (src->tail == tmp)
        src->tail = NULL;

    tmp->next = dest->head;
    dest->head = tmp;
    if (!dest->tail)
        dest->tail = tmp;
}
void push_swap(t_stack *a, t_stack *b, int count)
{
	int i = 0;
	int j;
	int bits = count - 1;
	while (bits >> i)
	{
		j = 0;
		while (j < count)
		{
			
			if (((a->head->rank >> i) & 1) == 0)
			{
				push(a, b);
				ft_printf("pb\n");
			}
			
			else 
			{
				rotate(a);	
				ft_printf("ra\n");
			}
			
			j++;
		}
		
		while (b->head)
		{
			push(b, a);
			ft_printf("pa\n");
		}
		
		i++;
	}
}
void sort_3(t_stack *a)
{
	int first = a->head->rank;
	int sec = a->head->next->rank;
	int third = a->head->next->rank;

	if (first == 0 && sec == 1 && third == 2)
		return;
	else if (third == 2)
	{
		swap(a);
		ft_printf("sa\n");
	}
	else if (first == 2)
	{
		if (sec == 0)
		{
			rotate(a);
			ft_printf("ra\n");
		}
		else 
		{
			swap(a);
			rev_rotate(a);
			ft_printf("sa\n");
			ft_printf("rra\n");
		}
	}
	else 
	{
		if (first == 0)
		{
			swap(a);
			rotate(a);
			ft_printf("sa\n");
			ft_printf("ra\n");
		}
		else {
			rev_rotate(a);
			ft_printf("rra\n");
		}
	}

}

void sort_4_5(t_stack *a, t_stack *b)
{
	int i = 0;
	int rank = a->head->rank;
	int target = 0;
	while (i < 2)
	{
		if (rank == target)
		{
			push(a, b);
			ft_printf("pb\n");
			target++;
		}
		else 
		{
			rotate(a);
			ft_printf("ra\n");
		}
		i++;
	}
	sort_3(a);
	i = 0;
	while (i < 2)
	{
		push(b, a);
		ft_printf("pa\n");
		i++;
	}

}

void small_sort(t_stack *a, t_stack *b, int count)
{
	if (count == 2)
	{
		if (a->head->rank > a->head->next->rank)
			ft_printf("sa\n");
	}
	else if (count == 3)
		sort_3(a);
	else 
		sort_4_5(a, b);
}

int main(int argc, char *argv[])
{
	t_stack stack_a;
	t_stack stack_b;
	int *tokens;
	int num_count = 0;
	
	ft_memset(&stack_b, 0, sizeof(stack_b));
	ft_memset(&stack_a, 0, sizeof(stack_a));
	if (argc < 2 || !argv[1][0])
		error_mssg("Error\n");
	tokens = parse_input(++argv, &num_count);
	check_duplicates(tokens, num_count);
	load_stack_a(tokens, &stack_a, num_count);
	quick_sort(tokens, 0, num_count - 1);
	ranking(tokens, &stack_a, num_count);
	if (num_count <= 5)
		small_sort(&stack_a, &stack_b, num_count);
	else
		push_swap(&stack_a, &stack_b, num_count);
	
}
