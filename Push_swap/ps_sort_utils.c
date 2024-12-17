/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:07:49 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/13 13:01:30 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_rot_sort(t_stack *stack)
{
	int	a;
	int	b;
	int	c;

	a = stack->head->data;
	b = stack->head->next->data;
	c = stack->head->next->next->data;
	if (a < b && b < c)
		return (1);
	if (b < c && a > c)
		return (1);
	if (c < a && a < b)
		return (1);
	return (0);
}

void	simple_sort(t_stack *stack, int length)
{
	int	min_s_index;
	int	c;

	if (is_stack_sorted(stack))
		return ;
	min_s_index = find_min_index(stack);
	c = count_index(stack->head, min_s_index);
	if (is_rot_sort(stack))
	{
		if (c < length - c)
			ops_rotate(stack, 'a', TRUE);
		else
			ops_reverse_rotate(stack, 'a', TRUE);
	}
	else
	{
		ops_swap(stack, 'a', TRUE);
		if (is_stack_sorted(stack))
			return ;
		if (c < length - c)
			ops_rotate(stack, 'a', TRUE);
		else
			ops_reverse_rotate(stack, 'a', TRUE);
	}
}

void	s_insertion_sort(t_stack *stack_a, t_stack *stack_b, int length)
{
	int	min_index;
	int	remaining;

	remaining = length - 3;
	while (remaining--)
	{
		min_index = find_min_index(stack_a);
		while (stack_a->head->s_index != min_index)
		{
			if (count_index(stack_a->head, min_index) <= stack_a->size / 2)
				ops_rotate(stack_a, 'a', TRUE);
			else
				ops_reverse_rotate(stack_a, 'a', TRUE);
		}
		ops_push(stack_a, stack_b, 'b', TRUE);
	}
	simple_sort(stack_a, 3);
	while (stack_b->size > 0)
		ops_push(stack_b, stack_a, 'a', TRUE);
}

void	k_sort1(t_stack *stack_a, t_stack *stack_b, int length)
{
	int	i;
	int	range;

	i = 0;
	range = ft_sqrt(length) * 14 / 10;
	while (stack_a->head)
	{
		if (stack_a->head->s_index <= i)
		{
			ops_push(stack_a, stack_b, 'b', TRUE);
			i++;
		}
		else if (stack_a->head->s_index <= i + range)
		{
			ops_push(stack_a, stack_b, 'b', TRUE);
			ops_rotate(stack_b, 'b', TRUE);
			i++;
		}
		else
			ops_rotate(stack_a, 'a', TRUE);
	}
}

void	k_sort2(t_stack *stack_a, t_stack *stack_b, int length)
{
	while (length--)
	{
		if (count_index(stack_b->head, length) <= stack_b->size / 2)
		{
			while (stack_b->head->s_index != length)
				ops_rotate(stack_b, 'b', TRUE);
		}
		else
		{
			while (stack_b->head->s_index != length)
				ops_reverse_rotate(stack_b, 'b', TRUE);
		}
		ops_push(stack_b, stack_a, 'a', TRUE);
	}
}
