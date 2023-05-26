/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:35:39 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:35:39 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_copy_from_list(t_env_node *head)
{
	int		size;
	char	**my_env;
	int		i;
	char	*value;

	i = 0;
	size = get_list_size(head);
	my_env = malloc((size + 1) * sizeof(char *));
	if (!my_env)
		return (NULL);
	while (i < size)
	{
		if (head->type == ASSIGNED)
		{
			value = ft_strjoin(head->var, "=");
			value = ft_strjoin(value, head->value);
			if (!value)
				return (NULL);
			my_env[i] = ft_sp_strdup(value, "");
			i++;
		}
		head = head->next;
	}
	my_env[i] = NULL;
	return (my_env);
}

void	execute_cmd(t_console *console)
{
	t_definer	*definer;
	int			i;

	console->env = ft_copy_from_list(console->head_env);
	i = 0;
	definer = console->definer;
	if (definer->type == COMMAND)
	{
		execve(definer->cmds[0], definer->cmds, console->env);
		write_in_stderror(definer->cmds[0]);
	}
	else
	{
		execute_build_in(console);
		exit(0);
	}
}

int	get_list_size(t_env_node *head)
{
	int	size;

	size = 0;
	while (head)
	{
		if (head->type == ASSIGNED)
			size++;
		head = head->next;
	}
	return (size);
}

void	execute(t_console *console, int index, int *fd)
{
	int	build_in;

	build_in = is_command_build_in(console->definer->cmds[0]);
	console->definer->type = build_in;
	if (console->number_command == 1 && console->definer->type > COMMAND)
	{
		execute_build_in(console);
	}
	else
	{
		execute_multiple_commands(console, fd, index);
	}
}
