/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:22:48 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:22:48 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '-')
	{
		i++;
		while (s[i] && s[i] == 'n')
			i++;
		if (!s[i] && i > 1)
			return (1);
		return (0);
	}
	return (0);
}

void	print_content_echo(int flag, t_definer *definer)
{
	int	i;

	i = 2;
	if (flag == 0)
	{
		write(definer->out, definer->cmds[1], ft_strlen(definer->cmds[1]));
		while (definer->cmds[i])
		{
			write(definer->out, " ", 1);
			ft_putstr_fd(definer->cmds[i], definer->out);
			i++;
		}
	}
	else
	{
		while (definer->cmds[i] && return_line(definer->cmds[i]) == 1)
			i++;
		while (definer->cmds[i])
		{
			ft_putstr_fd(definer->cmds[i], definer->out);
			i++;
			if (definer->cmds[i])
				write(definer->out, " ", 1);
		}
	}
}

void	echo(t_console *console)
{
	int			flag;
	t_definer	*definer;

	g_err_code = 0;
	definer = console->definer;
	flag = return_line(definer->cmds[1]);
	if (definer->cmds[1])
		print_content_echo(flag, definer);
	if (flag == 0)
		write(definer->out, "\n", 1);
}
