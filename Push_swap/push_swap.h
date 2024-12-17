/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:32:58 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/13 12:57:53 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>

typedef struct s_node
{
	int				data;
	int				s_index;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	int		size;
}	t_stack;

/*ps_ops_stack.c*/
void	push_stack(t_stack *stack, int index, int data);
int		del_stack(t_stack *stack);

/*ps_ops.c*/
void	ops_swap(t_stack *stack, char x, t_bool b);
void	ops_push(t_stack *stack1, t_stack *stack2, char x, t_bool b);
void	ops_rotate(t_stack *stack, char x, t_bool b);
void	ops_reverse_rotate(t_stack *stack, char x, t_bool b);

/*ps_ops2.c*/
void	ops_swap_both(t_stack *stack_a, t_stack *stack_b);
void	ops_rotate_both(t_stack *stack_a, t_stack *stack_b);
void	ops_reverse_rotate_both(t_stack *stack_a, t_stack *stack_b);

/*ps_parsing.c*/
int		count_nmb(int argc, char **argv);
void	check_limits(char *num_str);
void	check_repeated(int *array, int count);
void	fill_array(int argc, char **argv, int *array);
int		*parse_input(int argc, char **argv, int *count);

/*ps_sort_utils.c*/
int		is_rot_sort(t_stack *stack);
void	simple_sort(t_stack *stack, int length);
void	s_insertion_sort(t_stack *stack_a, t_stack *stack_b, int length);
void	k_sort1(t_stack *stack_a, t_stack *stack_b, int length);
void	k_sort2(t_stack *stack_a, t_stack *stack_b, int length);

/*ps_sort.c*/
int		find_min_index(t_stack *stack);
int		count_index(t_node *stack, int index);
int		is_stack_sorted(t_stack *stack);
void	free_stack(t_stack *stack);
void	sort(t_stack *stack_a, t_stack *stack_b, int *numbers, int length);

/*push_swap.c*/
int		main(int argc, char **argv);
void	init_ps(t_stack *stack_a, t_stack *stack_b, int *array, int size);

#endif