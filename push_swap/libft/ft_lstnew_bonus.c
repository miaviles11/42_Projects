/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:00:34 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/08 18:15:09 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list) * 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*int main (void)
{
	t_list *node = ft_lstnew("Hola mundo");

	if (node == NULL)
	{
		printf("Error\n");
		return (1);
	}

	printf("Nodo: %s\n", (char *)node->content);
	free(node);

	return(0);
}*/