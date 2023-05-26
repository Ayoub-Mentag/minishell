/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:00:53 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 16:00:53 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_block **head)
{
	t_block	*curr;
	t_block	*next_lst;

	if (!head)
		exit(1);
	curr = *head;
	while (curr != NULL)
	{
		next_lst = curr->next;
		free(curr);
		curr = next_lst;
	}
	*head = NULL;
}

void	free_blocks(t_block **head)
{
	t_block	*tmp;

	if (!head)
		exit(1);
	tmp = *head;
	while (tmp)
	{
		free(tmp->block_of_memory);
		tmp = tmp->next;
	}
	ft_lstclear(head);
}

void	init_block(t_block *block, void *alocated)
{
	block->block_of_memory = alocated;
	block->next = NULL;
}

void	*ft_malloc(size_t size)
{
	void	*alocated;

	alocated = malloc(size);
	collect(alocated);
	return (alocated);
}
