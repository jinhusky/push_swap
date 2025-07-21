/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:19:58 by kationg           #+#    #+#             */
/*   Updated: 2025/07/21 14:14:04 by kationg          ###   ########.fr       */
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
		if (d_arr[i][j] == '-' && ft_isdigit(d_arr[i][j + 1]))
			j++;
		while (d_arr[i][j])
		{
			if (!ft_isdigit(d_arr[i][j]) || d_arr[i][j] == '\0')
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

	if (**argv == '\0')
		error_mssg("Error\n");
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
				error_mssg("Error\n");
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
	while (ptr->next != stack->tail)
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

int is_sorted(t_stack *a)
{
	t_node *ptr = a->head;
	while (ptr && ptr->next)
	{
		if (ptr->rank > ptr->next->rank)
			return 0;
		ptr = ptr->next;
	}
	return (1);
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
void sort_3(t_stack *a, int count)
{ 
	int first = a->head->rank - (count - 3);
	int sec = a->head->next->rank - (count - 3);
	int third = a->head->next->next->rank - (count - 3);

	if (first == 0 && sec == 1 && third == 2)
		return;
	else if (third == 2)
		ft_printf("sa\n");
	else if (first == 2)
	{
		if (sec == 0)
			ft_printf("ra\n");
		else 
		{
			ft_printf("sa\n");
			ft_printf("rra\n");
		}
	}
	else 
	{
		if (first == 0)
		{
			ft_printf("sa\n");
			ft_printf("ra\n");
		}
		else 
			ft_printf("rra\n");
	}

}
void moves(t_stack *a, int target)
{
	t_node *ptr = a->head;
	int count = 0;
	while (ptr)
	{
		if (ptr->rank == target)
			break;
		ptr = ptr->next;
		count++;
	}
	if (count >= 3)
	{
		rev_rotate(a);
		ft_printf("rra\n");
	}
	else {
		rotate(a);
		ft_printf("ra\n");
	}

}

void sort_4_5(t_stack *a, t_stack *b, int count)
{
	int i = 0;
	int target = 0;
	while (i < count - 3)
	{
		if (a->head->rank == target)
		{
			push(a, b);
			ft_printf("pb\n");
			target++;
			i++;
		}
		else 
			moves(a, target);
	}
	sort_3(a, count);
	i = 0;
	while (i < count - 3)
	{
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
		sort_3(a, count);
	else 
		sort_4_5(a, b, count);
}

int main(int argc, char *argv[])
{
  (void) argc;
	t_stack stack_a;
	t_stack stack_b;
	int *tokens;
	int num_count = 0;
	
	ft_memset(&stack_b, 0, sizeof(stack_b));
	ft_memset(&stack_a, 0, sizeof(stack_a));
	tokens = parse_input(++argv, &num_count);
	check_duplicates(tokens, num_count);
	load_stack_a(tokens, &stack_a, num_count);
	quick_sort(tokens, 0, num_count - 1);
	ranking(tokens, &stack_a, num_count);
	if (is_sorted(&stack_a))
		exit(0);
	if (num_count <= 5)
		small_sort(&stack_a, &stack_b, num_count);
	else
		push_swap(&stack_a, &stack_b, num_count);
	
}
