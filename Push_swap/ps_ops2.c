/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_ops_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:05:13 by miaviles          #+#    #+#             */
/*   Updated: 2024/11/26 17:23:12 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ops_swap_both(t_stack *stack_a, t_stack *stack_b)
{
	ops_swap(stack_a, 'a', FALSE);
	ops_swap(stack_b, 'b', FALSE);
	write(1, "ss\n", 3);
}

void	ops_rotate_both(t_stack *stack_a, t_stack *stack_b)
{
	ops_rotate(stack_a, 'a', FALSE);
	ops_rotate(stack_b, 'b', FALSE);
	write(1, "rr\n", 3);
}

void	ops_reverse_rotate_both(t_stack *stack_a, t_stack *stack_b)
{
	ops_reverse_rotate(stack_a, 'a', FALSE);
	ops_reverse_rotate(stack_b, 'b', FALSE);
	write(1, "rrr\n", 4);
}
