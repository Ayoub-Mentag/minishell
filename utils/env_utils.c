/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 06:27:20 by amentag           #+#    #+#             */
/*   Updated: 2023/04/09 22:38:03 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_node	*get_min(t_env_node *head)
{
	t_env_node	*min;
	t_env_node	*tmp;

	tmp = head;
	min = head;
	while (min && min->index != -1)
		min = min->next;
	while (tmp)
	{
		if (tmp && ft_strcmp(tmp->var, min->var) < 0 && tmp->index == -1)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

int	ft_env_size(t_env_node *head)
{
	int	size;

	size = 0;
	while (head)
	{
		head = head->next;
		size++;
	}
	return (size);
}

void	ft_sort_head_env(t_env_node *head)
{
	t_env_node	*min;
	int			i;
	int			size;

	i = 0;
	size = ft_env_size(head);
	while (i < size)
	{
		min = get_min(head);
		min->index = i;
		i++;
	}
}

void	trim_cmd(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && (line[i] != '|' || is_valid_pipe(line, i) != 1))
		i++;
	i++;
	while (line[i])
	{
		line[j] = line[i];
		i++;
		j++;
	}
	while (line[j])
	{
		line[j] = '\0';
		j++;
	}
}
