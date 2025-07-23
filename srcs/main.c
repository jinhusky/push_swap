/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:19:58 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 02:29:22 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	radix_sort(t_stack *a, t_stack *b, int count)
{
	int	i;
	int	j;
	int	bits;

	i = 0;
	bits = count - 1;
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

void	small_sort(t_stack *a, t_stack *b, int count)
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

int	main(int argc, char *argv[])
{
	t_stack	stack_a;
	t_stack	stack_b;
	int		*tokens;
	int		num_count;

	num_count = 0;
	(void) argc;
	if (argc < 2)
		exit(1);
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
		radix_sort(&stack_a, &stack_b, num_count);
}
