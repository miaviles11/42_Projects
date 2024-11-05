/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:19:25 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 18:46:21 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

/*int main(void)
{
	t_list *list = NULL;

	t_list *node1 = ft_lstnew(ft_strdup("Primer nodo"));
	t_list *node2 = ft_lstnew(ft_strdup("Segundo nodo"));
	t_list *node3 = ft_lstnew(ft_strdup("Tercer nodo"));

	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);

	t_list *list2 = list;

	while (list2)
	{
		printf("%s\n", (char *)list2-> content);
		list2 = list2->next;
	}

	while (list)
	{
		t_list *free_list = list;
		ft_lstdelone(free_list);
		list = list->next;
	}

	return (0);
}*/