/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:16:12 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/17 13:52:59 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_index(t_stack *stack)
{
	t_node	*current;
	int		min_index;

	if (!stack || !stack->head)
		return (-1);
	current = stack->head;
	min_index = current->s_index;
	while (current)
	{
		if (current->s_index < min_index)
			min_index = current->s_index;
		current = current->next;
	}
	return (min_index);
}

int	count_index(t_node *stack, int index)
{
	int	counter;

	if (!stack)
		return (-1);
	counter = 0;
	while (stack)
	{
		if (stack->s_index == index)
			return (counter);
		stack = stack->next;
		counter++;
	}
	return (0);
}

int	is_stack_sorted(t_stack *stack)
{
	t_node	*tmp;

	if (!stack || !stack->head || !stack->head->next)
		return (1);
	tmp = stack->head;
	while (tmp->next)
	{
		if (tmp->data > tmp->next->data)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	while (stack)
		del_stack(stack);
}

void	sort(t_stack *stack_a, t_stack *stack_b, int *numbers, int length)
{
	if (is_stack_sorted(stack_a))
	{
		free_stack(stack_a);
		ft_error_clean("", FALSE, numbers);
	}
	if (length == 2)
	{
		if (stack_a->head->data > stack_a->head->next->data)
			ops_swap(stack_a, 'a', TRUE);
	}
	else if (length == 3)
		simple_sort(stack_a, length);
	else if (length <= 7)
		s_insertion_sort(stack_a, stack_b, length);
	else if (length > 7)
	{
		k_sort1(stack_a, stack_b, length);
		k_sort2(stack_a, stack_b, length);
	}
	else
		ft_error("", TRUE);
}
