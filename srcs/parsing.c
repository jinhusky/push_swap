/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:27:00 by kationg           #+#    #+#             */
/*   Updated: 2025/07/24 13:54:00 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	not_digit(char **d_arr)
{
	int	i;
	int	j;

	i = 0;
	while (d_arr[i])
	{
		j = 0;
		if (d_arr[i][j] == '-' && ft_isdigit(d_arr[i][j + 1]))
			j++;
		while (d_arr[i][j])
		{
			if (!ft_isdigit(d_arr[i][j]) || d_arr[i][j] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

//count the length to allocate for token d_array 
//and also check for invalid arguments(char etc)
static int	count_numbers(char **argv)
{
	char	**subarr;
	int		len;
	int		i;

	len = 0;
	if (**argv == '\0')
		error_mssg("Error\n", NULL, NULL);
	while (*argv)
	{
		i = 0;
		subarr = ft_split(*argv, ' ');
		while (subarr[i])
		{
			if (not_digit(subarr))
			{
				free_2d_arr(subarr);
				error_mssg("Error\n", NULL, NULL);
			}
			len++;
			i++;
		}
		free_2d_arr(subarr);
		argv++;
	}
	return (len);
}

//now i know why zero is breaking my code because the while loop 
//checks for arr[i] null terminator which triggers the zero
void	check_duplicates(int *arr, int length)
{
	int	i;
	int	j;

	i = 0;
	while (i < length)
	{
		j = i + 1;
		while (j < length)
		{
			if (arr[i] == arr[j])
				error_mssg("Error\n", NULL, arr);
			j++;
		}
		i++;
	}
}

//where i first parse the input by splitting the 
//argv if i has multiple digits then adding to res one by one
int	*parse_input(char **argv, int *num_count)
{
	int		i;
	int		j;
	int		len;
	char	**subarr;
	int		*res;

	i = 0;
	len = 0;
	*num_count = count_numbers(argv);
	res = ft_calloc(sizeof(int *), count_numbers(argv));
	while (argv[i])
	{
		j = 0;
		subarr = ft_split(argv[i], ' ');
		while (subarr[j])
		{
			res[len] = ft_atoi(subarr[j]);
			len++;
			j++;
		}
		free_2d_arr(subarr);
		i++;
	}
	return (res);
}
