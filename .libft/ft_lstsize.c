/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:15:07 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 14:54:33 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lstlen;

	lstlen = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		lstlen++;
	}
	return (lstlen);
}

/* int main(void)
{
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	t_list *node4 = ft_lstnew("Node 4");

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL; 

	int size = ft_lstsize(node1);

	printf("Taille liste: %d\n", size);

	return (0);
} */

//gcc -Wall -Wextra -Werror ft_lstsize.c ft_lstnew.c -o prog