/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:57:11 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 02:24:39 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct s_node
{
	int				value;
	int				rank;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	size_t	size;
	t_node	*head;
	t_node	*tail;
}	t_stack;

void	radix_sort(t_stack *a, t_stack *b, int count);
void	small_sort(t_stack *a, t_stack *b, int count);

//operations.c
void	swap(t_stack *stack);
void	rev_rotate(t_stack *stack);
void	rotate(t_stack *stack);
void	push(t_stack *src, t_stack *dest);

//parsing.c
void	check_duplicates(int *arr, int length);
int		*parse_input(char **argv, int *num_count);

//ranking.c
void	quick_sort(int *array, int low, int high);
void	ranking(int *array, t_stack *stack, int num_count);

//small_sorts.c
int		is_sorted(t_stack *a);
void	sort_3(t_stack *a, int count);
void	sort_4_5(t_stack *a, t_stack *b, int count);

//utils
void	error_mssg(char *mssg);
void	free_2d_arr(char **d_arr);
t_node	*create_node(int num);
void	load_stack_a(int *tokens, t_stack *stack_a, int length);

#endif
