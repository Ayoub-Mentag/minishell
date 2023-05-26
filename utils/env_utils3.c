/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:32:04 by amentag           #+#    #+#             */
/*   Updated: 2023/04/11 23:32:09 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envadd_back(t_env_node **head, t_env_node *new)
{
	t_env_node	*last_node;

	last_node = *head;
	if (!head || !new)
		return ;
	if (!last_node)
		*head = new;
	else
	{
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new;
	}
}

void	ft_env_clear(t_env_node **head)
{
	t_env_node	*tmp;

	if (head == NULL)
		return ;
	while ((*head) != NULL)
	{
		tmp = (*head)->next;
		free((*head)->value);
		free((*head)->var);
		free(*head);
		*head = tmp;
	}
}
