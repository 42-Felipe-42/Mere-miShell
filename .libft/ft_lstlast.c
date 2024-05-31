/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:13:07 by plangloi          #+#    #+#             */
/*   Updated: 2023/11/16 14:57:53 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

/* 
int main(void)
{
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");
	t_list *node4 = ft_lstnew("Yopa");
    
	node1->next = node2;
    node2->next = node3;
    node3->next = node4;
	node4->next = NULL;

    t_list *lastNode = ft_lstlast(node1);

    if (lastNode)
        printf("Last node content: %s\n", (char *)lastNode->content);
    else
        printf("List is empty.\n");

    return (0);
}
 */