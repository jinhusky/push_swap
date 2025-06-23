/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:37:03 by kationg           #+#    #+#             */
/*   Updated: 2025/06/23 10:43:15 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;
	int	number;

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
		if (number > (INT_MAX - (str[i] - '0')) / 10 ||
				number < (INT_MIN + (str[i] - '0') * 10))
		{
			ft_printf("\nERROR\nInput number exceeds the limits of a 32-bit signed integer");
			exit(1);
		}
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * negative);
}
