/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:02:43 by amentag           #+#    #+#             */
/*   Updated: 2023/04/12 14:20:49 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	collect(void *alocated)
{
	static t_block	*head;
	t_block			*last;
	t_block			*new;

	if (alocated == NULL)
		return (free_blocks(&head), 0);
	if (head == NULL)
	{
		head = malloc(sizeof(t_block));
		if (!head)
			return (free_blocks(&head), 1);
		init_block(head, alocated);
	}
	else
	{
		last = head;
		while (last->next)
			last = last->next;
		new = malloc(sizeof(t_block));
		if (!new)
			return (free_blocks(&head), 1);
		init_block(new, alocated);
		last->next = new;
	}
	return (1);
}
