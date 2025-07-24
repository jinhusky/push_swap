/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sorts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:42:10 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 09:42:44 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	moves(t_stack *a, int target)
{
	t_node	*ptr;
	int		count;

	ptr = a->head;
	count = 0;
	while (ptr)
	{
		if (ptr->rank == target)
			break ;
		ptr = ptr->next;
		count++;
	}
	if (count >= 3)
	{
		rev_rotate(a);
		ft_printf("rra\n");
	}
	else
	{
		rotate(a);
		ft_printf("ra\n");
	}
}

int	is_sorted(t_stack *a)
{
	t_node	*ptr;

	ptr = a->head;
	while (ptr && ptr->next)
	{
		if (ptr->rank > ptr->next->rank)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

static void	sort_3_helper(int first, int sec, int third)
{
	if (first == 0 && sec == 1 && third == 2)
		return ;
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

void	sort_3(t_stack *a, int count)
{
	int	first;
	int	sec;
	int	third;

	first = a->head->rank - (count - 3);
	sec = a->head->next->rank - (count - 3);
	third = a->head->next->next->rank - (count - 3);
	sort_3_helper(first, sec, third);
}

void	sort_4_5(t_stack *a, t_stack *b, int count)
{
	int	i;
	int	target;

	i = 0;
	target = 0;
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
