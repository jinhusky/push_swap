/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:57:11 by kationg           #+#    #+#             */
/*   Updated: 2025/06/11 09:11:25 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../libft/libft.h"

typedef struct s_node
{
	int value;
	struct s_node *next;
	struct s_node *prev;
} t_node;

typedef struct s_stack
{
	size_t size;
	t_node *head;
}t_stack;

#endif
