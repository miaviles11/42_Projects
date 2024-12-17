/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:24:25 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/17 13:50:35 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_ps(t_stack *stack_a, t_stack *stack_b, int *array, int size)
{
	int		i;
	t_node	*temp;

	if (!array || size <= 0)
		ft_error("Error\n", TRUE);
	stack_a->head = NULL;
	stack_a->size = 0;
	stack_b->head = NULL;
	stack_b->size = 0;
	i = size - 1;
	while (i >= 0)
	{
		push_stack(stack_a, 0, array[i]);
		i--;
	}
	ft_bubblesort(array, size);
	temp = stack_a->head;
	while (temp)
	{
		temp->s_index = ft_index(temp->data, array);
		temp = temp->next;
	}
}

int	main(int argc, char **argv)
{
	int		count;
	t_stack	stack_a;
	t_stack	stack_b;
	int		*array;

	if (argc == 1)
		return (0);
	array = parse_input(argc, argv, &count);
	if (!array)
		ft_error("Error\n", TRUE);
	init_ps(&stack_a, &stack_b, array, count);
	sort(&stack_a, &stack_b, array, count);
	free(array);
	free_stack(&stack_a);
	return (0);
}
