/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:52:59 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 20:13:21 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst2;

	if (!del)
		return ;
	while (*lst)
	{
		lst2 = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = lst2;
	}
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
        printf("%s\n", (char *)list2->content);
        list2 = list2->next;
    }

	ft_lstclear(&list, &free);

	if (list == NULL)
	{
		printf("Se han eliminado los nodos\n");
	}
	else
	{
		printf("No se han eliminado todos los nodos\n");
	}
	return (0);
}*/