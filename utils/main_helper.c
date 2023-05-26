/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:27:54 by amentag           #+#    #+#             */
/*   Updated: 2023/04/14 02:44:16 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_in_out_and_unlink(t_console *cont)
{
	if (cont->definer->in != 0)
		close(cont->definer->in);
	if (cont->definer->out != 1)
		close(cont->definer->out);
	if (cont->heredoc_file_name)
	{
		unlink(cont->heredoc_file_name);
		cont->heredoc_file_name = NULL;
	}
}

void	ft_loop_cmd(t_console *cont, char *str)
{
	int			i;
	int			fd[2];
	static int	j;

	i = -1;
	fd[0] = -1;
	fd[1] = -1;
	if (cont && g_err_code == 0)
	{
		while (++i < cont->number_command)
		{
			if (ft_curr_cmd_contains_heredoc(cont, i))
				open_and_write_to_heredoc(cont, i);
			ft_parsing(str, cont, 0);
			if (cont->definer->cmds)
				execute(cont, i, fd);
			close_in_out_and_unlink(cont);
			if (i <= cont->number_command - 1)
				ft_rest(cont, str);
		}
		ft_close(fd[0]);
		while (wait(0) != -1 || errno != ECHILD)
			j++;
	}
	collect(NULL);
}

void	ft_run(t_console *console, char *str)
{
	t_cmds		*command;

	if (!check_str(console, str))
		return ;
	console->number_command = calcule_command(str);
	command = ft_malloc(console->number_command * sizeof(t_cmds));
	if (!command)
		free_console(console, 1);
	ft_loop_cmd(console, str);
}

char	*get_telda(t_env_node *head_env)
{
	char	*home;
	char	*telda;
	int		len;

	len = 0;
	home = ft_expand_var(head_env, "PWD");
	len++;
	while (home[len] != '/')
		len++;
	len++;
	while (home[len] != '/')
		len++;
	telda = malloc(len + 1);
	if (!telda)
		return (NULL);
	ft_strlcpy(telda, home, len + 1);
	return (telda);
}
