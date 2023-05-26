/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:47:48 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:47:48 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_sorted(t_env_node *head)
{
	t_env_node	*tmp;
	int			size;
	int			i;

	i = 0;
	size = ft_env_size(head);
	while (i < size)
	{
		tmp = head;
		while (tmp && tmp->index != i)
			tmp = tmp->next;
		if (tmp->index == i)
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
			else
				printf("declare -x %s\n", tmp->var);
		}
		i++;
	}
}

t_env_node	*get_last_env_node(t_env_node *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_set_index_and_update(t_env_node *head, t_env_node *node)
{
	t_env_node	*tmp;
	int			index;

	index = 0;
	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, node->var) > 0 && node->index > tmp->index)
		{
			node->index = tmp->index;
		}
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp)
	{
		if (tmp->index >= node->index && ft_strcmp(node->var, tmp->var))
			tmp->index += 1;
		tmp = tmp->next;
	}
}

void	ft_add_env(char *var, char *value, t_env_node *head)
{
	t_env_node	*node;
	t_env_node	*last;

	node = malloc(sizeof(t_env_node));
	if (!node)
		exit(1);
	last = get_last_env_node(head);
	node->var = var;
	node->value = value;
	node->index = ft_env_size(head);
	node->next = NULL;
	ft_set_index_and_update(head, node);
	last->next = node;
	node->type = ASSIGNED;
	if (!(node->value))
		node->type = NOTASSIGNED;
}

int	check_var_name(char *s)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(s);
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		error_var(s);
		return (0);
	}
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] && s[i + 1] == '=')
			return (1);
		else if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
		{
			error_var(s);
			return (0);
		}
		i++;
	}
	return (1);
}
