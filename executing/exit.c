/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:35:53 by amentag           #+#    #+#             */
/*   Updated: 2023/04/14 14:49:52 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_error(char *s)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_err_code = 255;
}

int	check_arg_numeric(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	my_exit_helper(t_console *console)
{
	if (console->definer->cmds[1] && \
	!check_arg_numeric(console->definer->cmds[1]))
		show_error(console->definer->cmds[1]);
	else
	{
		ft_putstr_fd("exit\n", 2);
		g_err_code = 0;
		if (console->definer->cmds[1])
			g_err_code = ft_atoi(console->definer->cmds[1]);
		if (g_err_code < 0)
			g_err_code += 256;
	}
	g_err_code %= 256;
}

void	my_exit_helper2(t_console *console)
{
	int	args;

	args = 0;
	while (console->definer->cmds[args])
			args++;
	if (args <= 2)
		my_exit_helper(console);
	else if (args > 2)
	{
		if (console->definer->cmds[1] && \
			!check_arg_numeric(console->definer->cmds[1]))
			show_error(console->definer->cmds[1]);
		else
		{
			g_err_code = 1;
			return (ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2));
		}
	}
	collect(NULL);
	free(console->telda);
	ft_env_clear(&(console->head_env));
	free(console->definer);
	free(console->secure_path);
	free(console);
	exit(g_err_code);
}

void	my_exit(t_console *console)
{
	if (console->definer->cmds[1])
		my_exit_helper2(console);
	else
	{
		ft_putstr_fd("exit\n", 1);
		if (console->definer->out != 1)
			close(console->definer->out);
		if (console->definer->in != 0)
			close(console->definer->in);
		g_err_code = 0;
		free_console(console, g_err_code);
	}
}
