/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:36:37 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/14 12:47:26 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static void *ft_dup(void *content)
{
    return (ft_strdup((char *)content));
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*node;

	if (lst == NULL || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		node = ft_lstnew(NULL);
		if (!node)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		node->content = f(lst->content);
		ft_lstadd_back(&list, node);
		lst = lst->next;
	}
	return (list);
}

/*int main(void)
{
	t_list *list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Primer nodo")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("Segundo nodo")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("Tercer nodo")));

	t_list *new_list = ft_lstmap(list, ft_dup, &free);

	t_list *list2 = new_list;
	while (list2)
	{
		printf("%s\n", (char *)list2->content);
		list2 = list2->next;
	}

	ft_lstclear(&list, &free);
    ft_lstclear(&new_list, &free);

	return (0);
}*/