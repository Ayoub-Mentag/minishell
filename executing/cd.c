/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:21:26 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:21:26 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(t_console *console, char *new_pwd)
{
	int			ret;

	unset("PWD", &(console->head_env), console);
	if (!new_pwd)
	{
		g_err_code = 1;
		return ((void) ft_putstr_fd("-bash: cd: HOME not set\n", 2));
	}
	ret = chdir(new_pwd);
	if (ret != 0)
	{
		g_err_code = 1;
		free(new_pwd);
		write(2, "There is no dir ", 16);
		write(2, new_pwd, ft_strlen(new_pwd));
		write(2, "\n", 1);
	}
	else
	{
		g_err_code = 0;
		ft_add_env(ft_sp_strdup("PWD", ""), new_pwd, console->head_env);
	}
}

void	cd_handle_dots(t_console *console, char *path)
{
	char	*new_path;
	int		i;

	i = 1;
	if (path && path[i] == '.' && (path[i + 1] == ' ' || !path[i + 1]))
	{
		i = ft_strlen(console->current_dir) - 1;
		while (console->current_dir[i] && console->current_dir[i] != '/')
			i--;
		if (i == 0)
			i++;
		new_path = malloc(i + 1);
		ft_strlcpy(new_path, console->current_dir, i + 1);
		change_pwd(console, new_path);
	}
}

char	*ft_get_full_path(char *path, char *current_dir)
{
	size_t	i;

	i = 0;
	while (path[i] && path[i] == '/')
		i++;
	if (i == ft_strlen(path))
		return (ft_strdup("/"));
	i = 0;
	while (path[i] && path[i] != '/')
		i++;
	if (path[i] == '/' && path[i + 1] == 0)
		path[i] = 0;
	if (path[i] != '/')
		path = ft_strjoin(current_dir, ft_strjoin("/", path));
	return (path);
}

void	init_old_pwd(t_console *console)
{
	char	*pwd;
	char	*var;
	char	*value;

	unset("OLDPWD", &(console->head_env), console);
	pwd = ft_expand_var(console->head_env, "PWD");
	if (pwd)
	{
		var = ft_sp_strdup("OLDPWD", "");
		value = ft_sp_strdup(pwd, "");
		ft_add_env(var, value, console->head_env);
	}
}

void	cd(t_console *console)
{
	int		i;
	char	*path;
	char	**args_of_cd;

	args_of_cd = console->definer->cmds;
	i = 0;
	init_old_pwd(console);
	getcwd(console->current_dir, sizeof(console->current_dir));
	while (args_of_cd[i])
		i++;
	path = args_of_cd[1];
	if (path)
	{
		if (path[0] == '.')
		{
			cd_handle_dots(console, path);
			return ;
		}
		else
			path = ft_get_full_path(path, console->current_dir);
	}
	else
		path = ft_expand_var(console->head_env, "HOME");
	change_pwd(console, ft_sp_strdup(path, ""));
}
