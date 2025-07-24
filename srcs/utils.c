/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:37:14 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 13:58:01 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	error_mssg(char *mssg, t_stack *a, int *tokens)
{
	ft_putstr_fd(mssg, 2);
	ft_exit(a, tokens);
}

void	free_2d_arr(char **d_arr)
{
	int	i;

	i = 0;
	while (d_arr[i])
	{
		free(d_arr[i++]);
	}
	free(d_arr);
}

t_node	*create_node(int num)
{
	t_node	*ptr;

	ptr = malloc(sizeof(t_node));
	ptr->value = num;
	ptr->next = NULL;
	return (ptr);
}

void	load_stack_a(int *tokens, t_stack *stack_a, int length)
{
	t_node	*new;
	t_node	*ptr;
	int		i;

	i = 0;
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
