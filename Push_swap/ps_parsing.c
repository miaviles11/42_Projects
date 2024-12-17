/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:40:25 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/13 13:29:48 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_nmb(int argc, char **argv)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '+'
				&& argv[i][j] != '-' && argv[i][j] != ' ')
				ft_error("Error\n", TRUE);
			if ((argv[i][j] == '+' && !ft_isdigit(argv[i][j + 1]))
				|| (argv[i][j] == '-' && !ft_isdigit(argv[i][j + 1])))
				ft_error("Error\n", TRUE);
			if (ft_isdigit(argv[i][j]) && (argv[i][j + 1] == ' '
					|| argv[i][j + 1] == '\0'))
				count += 1;
			j++;
		}
		i++;
	}
	return (count);
}

void	check_limits(char *num_str)
{
	long	num;

	num = ft_atol(num_str);
	if (num > INT_MAX || num < INT_MIN)
		ft_error_clean("Error\n", TRUE, num_str);
}

void	check_repeated(int *array, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (array[i] == array[j])
				ft_error_clean("Error\n", TRUE, array);
			j++;
		}
		i++;
	}
}

void	fill_array(int argc, char **argv, int *array)
{
	int		i;
	int		j;
	int		index;
	char	**split;

	i = 1;
	index = 0;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			ft_error_clean("", TRUE, split);
		j = 0;
		while (split[j])
		{
			check_limits(split[j]);
			array[index++] = ft_atoi(split[j]);
			free(split[j]);
			j++;
		}
		free(split);
		i++;
	}
}

int	*parse_input(int argc, char **argv, int *count)
{
	int	*array;

	if (!argv[0])
		*count = 0;
	*count = count_nmb(argc, argv);
	if (*count == 0)
		ft_error("Error\n", TRUE);
	array = (int *)malloc(sizeof(int) * (*count));
	if (!array)
		ft_error("Error\n", TRUE);
	fill_array(argc, argv, array);
	check_repeated(array, *count);
	return (array);
}
