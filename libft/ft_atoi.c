/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:37:03 by kationg           #+#    #+#             */
/*   Updated: 2025/07/23 16:35:30 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

//this checks for numbers more than INT_MAX or less than 
//INT_MIN because im using long, the number will wrap 
//around first and then check making the error checking useless
static void	check_error(long num, int negative)
{
	long	max;

	max = 2147483647;
	if ((num > max && negative == 1)
		|| (num > (max + 1) && negative == -1))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		negative;
	long	number;

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
		check_error(number, negative);
		i++;
	}
	return ((int)number * negative);
}
