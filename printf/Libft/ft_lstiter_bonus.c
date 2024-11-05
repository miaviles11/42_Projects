/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:14:17 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 20:33:39 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static void	ft_print_list(void *content)
{
	printf("%s\n", (char *)content);
}*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

/*int main(void)
{
	t_list	*list = NULL;

	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Primer nodo")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("Segundo nodo")));
    ft_lstadd_back(&list, ft_lstnew(ft_strdup("Tercer nodo")));

	ft_lstiter(list, ft_print_list);

	return (0);
}*/