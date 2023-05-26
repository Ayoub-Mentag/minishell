/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:55:24 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/14 01:30:25 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_clean_cmd(char *str, int i)
{
	int		y;
	char	*cleaned_cmd;

	y = i;
	while (str[y] && (str[y] != ' ' || check_q(str, y) != 0) && \
	is_valid_pipe(str, y) != 1)
		y++;
	cleaned_cmd = ft_substr(str, i, y - i);
	if (!cleaned_cmd)
		return (NULL);
	ft_rmove_quote(cleaned_cmd);
	while (str[y])
	{
		str[i] = str[y];
		i++;
		y++;
	}
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	return (cleaned_cmd);
}

static char	*get_cmd_opts(char *str)
{
	int		i;
	char	*cmd;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] == 32)
		i++;
	cmd = ft_get_clean_cmd(str, i);
	return (cmd);
}

static char	**return_path(t_console *cont)
{
	char		**path;
	char		*all_path;

	if (cont->secure == 1)
		all_path = cont->secure_path;
	else
		all_path = ft_expand_var(cont->head_env, "PATH");
	if (all_path)
	{
		path = ft_split(all_path, ':');
		if (!path)
			return (free_console(cont, 1), NULL);
		return (path);
	}
	return (NULL);
}

static void	check_path(char **path, t_console *cont, char *cmds)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			cont->definer->cmds[0] = ft_strjoin(path[i], "/");
			cont->definer->cmds[0] = ft_strjoin(cont->definer->cmds[0], cmds);
			if (!cont->definer->cmds[0])
				free_console(cont, 1);
			if (access(cont->definer->cmds[0], F_OK) == 0)
			{
				return ;
			}
			i++;
		}
	}
	path = NULL;
	cont->definer->cmds[0] = cmds;
}

void	ft_store_cmd(char *str, int j, t_console *cont)
{
	int		i;
	int		options;
	char	*main_command;
	char	**path_name;

	i = 1;
	cont->definer->cmds = ft_malloc((ft_size_cmd(str, j) + 2) * sizeof(char *));
	if (!cont->definer->cmds)
		free_console(cont, 1);
	main_command = get_cmd_opts(str);
	if (!main_command)
		free_console(cont, 1);
	if (is_command_build_in(main_command) > COMMAND)
		cont->definer->cmds[0] = main_command;
	else if (main_command[0] == '/' || main_command[0] == '.')
		cont->definer->cmds[0] = main_command;
	else
	{
		path_name = return_path(cont);
		check_path(path_name, cont, main_command);
	}
	options = count_options(str, find_end_command(str));
	while (i <= options)
		cont->definer->cmds[i++] = get_cmd_opts(str);
	cont->definer->cmds[i] = NULL;
}
