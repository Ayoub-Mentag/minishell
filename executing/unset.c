/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:42:48 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:42:48 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_node	*get_previous_node(t_env_node *head, char *var_name)
{
	t_env_node	*previous;

	if (ft_strcmp(head->var, var_name))
	{
		previous = head;
		while (previous->next)
		{
			if (ft_strcmp(previous->next->var, var_name) == 0)
				return (previous);
			previous = previous->next;
		}
	}
	return (NULL);
}

void	update_env_list_index(t_env_node *head, int index)
{
	t_env_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->index > index)
			tmp->index -= 1;
		tmp = tmp->next;
	}
}

void	free_node_and_update(t_env_node *tmp, t_env_node *head, int index)
{
	if (tmp)
	{
		free(tmp->value);
		free(tmp->var);
		free(tmp);
	}
	if (index != -1)
		update_env_list_index(head, index);
}

void	unset_helper(char *var_name, t_env_node **head, int index)
{
	t_env_node	*next;
	t_env_node	*tmp;
	t_env_node	*previous;

	if (!check_var_name(var_name))
		return ;
	tmp = NULL;
	previous = get_previous_node(*head, var_name);
	if (!previous && ft_strcmp((*head)->var, var_name) == 0)
	{
		tmp = *head;
		index = tmp->index;
		next = (*head)->next;
		(*head)->next = NULL;
		*head = next;
	}
	else if (previous)
	{
		tmp = previous->next;
		next = tmp->next;
		previous->next = next;
		index = tmp->index;
	}
	free_node_and_update(tmp, *head, index);
}

void	unset(char *var_name, t_env_node **head, t_console *console)
{
	if (ft_strcmp(var_name, "_") == 0)
		return ;
	else if (ft_strcmp(var_name, "PATH") == 0 && console->secure == 1 \
	&& console->secure_path)
	{
		console->secure_path = NULL;
		console->secure = 0;
	}
	else
		unset_helper(var_name, head, -1);
}
