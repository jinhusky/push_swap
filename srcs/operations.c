/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:26:27 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 03:15:25 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap(t_stack *stack)
{
	t_node	*tmp;

	tmp = stack->head;
	stack->head = tmp->next;
	tmp->next = stack->head->next;
	stack->head->next = tmp;
}

void	rev_rotate(t_stack *stack)
{
	t_node	*tmp;
	t_node	*ptr;

	tmp = stack->tail;
	ptr = stack->head;
	while (ptr->next != stack->tail)
		ptr = ptr->next;
	ptr->next = NULL;
	stack->tail = ptr;
	tmp->next = stack->head;
	stack->head = tmp;
}

void	rotate(t_stack *stack)
{
	t_node	*tmp;

	tmp = stack->head;
	if (!stack->head || !tmp->next)
		return ;
	stack->head = tmp->next;
	tmp->next = NULL;
	stack->tail->next = tmp;
	stack->tail = tmp;
}

void	push(t_stack *src, t_stack *dest)
{
	t_node	*tmp;

	tmp = src->head;
	if (!src->head)
		return ;
	src->head = tmp->next;
	if (src->tail == tmp)
		src->tail = NULL;
	tmp->next = dest->head;
	dest->head = tmp;
	if (!dest->tail)
		dest->tail = tmp;
}
