/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:44:11 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 14:03:58 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void ft_exit(t_stack *a, int *tokens)
{
	t_node	*ptr;
	t_node	*next;

	ptr = a->head;
	if (tokens)
		free(tokens);
	tokens = NULL;
	while (ptr)
	{
		if (ptr->next)
			next = ptr->next;
		free(ptr);
		ptr = next;
	}

	exit(1);
}
