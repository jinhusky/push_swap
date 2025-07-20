/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:37:03 by kationg           #+#    #+#             */
/*   Updated: 2025/07/20 13:02:19 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;
	long number;
	long max;

	max = 2147483647;
	i = 0;
	number = 0;
	negative = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		if ((number > max && negative == 1) || (number > (max + 1) && negative == -1))
		{
			ft_printf("Error\n");
			exit(1);
		}
		i++;
	}
	return ((int)number * negative);
}
