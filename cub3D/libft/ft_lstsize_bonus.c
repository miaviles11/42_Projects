/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:50 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/09 13:26:47 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	size;

	size = 0;
	if (!lst)
		return (size);
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/*int main(void)
{
    t_list *list = NULL;

    list = ft_lstnew("Nodo 1");
    ft_lstadd_front(&list, ft_lstnew("Nodo 2")); 
    ft_lstadd_front(&list, ft_lstnew("Nodo 3")); 

    int size = ft_lstsize(list);
    printf("El tamaño de la lista es: %d\n", size);

    while (list)
    {
        t_list *free_list = list;
        list = list->next;
        free(free_list);
    }
	return (0);
}*/
