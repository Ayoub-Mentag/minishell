/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:13 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:31:13 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_build_in(t_console *console)
{
	char	*cmd;
	int		len;

	cmd = console->definer->cmds[0];
	len = ft_strlen(cmd);
	if (console->definer->type == CD)
		cd(console);
	else if (console->definer->type == ECHO)
		echo(console);
	else if (console->definer->type == ENV)
		print_env(console);
	else if (console->definer->type == PWD)
		print_pwd(console);
	else if (console->definer->type == EXPORT)
		export(console);
	else if (console->definer->type == UNSET)
		unset_vars(console);
	else if (console->definer->type == EXIT)
		my_exit(console);
	if (console->definer->out != 1)
		close(console->definer->out);
	if (console->definer->in != 0)
		close(console->definer->in);
	console->definer->out = 1;
	console->definer->in = 0;
}

void	write_in_stderror(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (errno == ENOENT)
	{
		write(2, "bash: ", 6);
		write(2, cmd, len);
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else if (errno == EACCES)
	{
		write(2, "minishel: ", 10);
		write(2, cmd, len);
		write(2, ": Permission denied\n", 20);
		exit(126);
	}
	exit(1);
}

void	ft_dup_input(t_console *console, int old_in_of_pipe, int index)
{
	if (console->definer->in != 0)
	{
		if (dup2(console->definer->in, STDIN_FILENO) == -1)
			return (ft_putstr_fd("dup2 failed\n", 2), exit(1));
		ft_close(console->definer->in);
	}
	else if (index > 0 && old_in_of_pipe != -1)
	{
		if (dup2(old_in_of_pipe, STDIN_FILENO) == -1)
			return (ft_putstr_fd("dup2 failed\n", 2), exit(1));
	}
}

void	ft_dup_output(t_console *console, int out, int index)
{
	if (console->definer->out != 1)
	{
		if (dup2(console->definer->out, STDOUT_FILENO) == -1)
			return (ft_putstr_fd("dup2 failed\n", 2), exit(1));
		ft_close(console->definer->out);
	}
	else if (index < console->number_command - 1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			return (ft_putstr_fd("dup2 failed\n", 2), exit(1));
	}
}

void	execute_multiple_commands(t_console *console, int *fd, int index)
{
	int	old_in_of_pipe;
	int	status;
	int	id;

	old_in_of_pipe = fd[0];
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		handle_sinagls();
		ft_close(fd[0]);
		ft_dup_input(console, old_in_of_pipe, index);
		ft_dup_output(console, fd[1], index);
		ft_close(old_in_of_pipe);
		ft_close(fd[1]);
		execute_cmd(console);
	}
	ft_close(fd[1]);
	ft_close(old_in_of_pipe);
	if (index == console->number_command -1)
	{
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
			g_err_code = WEXITSTATUS(status);
	}
}
