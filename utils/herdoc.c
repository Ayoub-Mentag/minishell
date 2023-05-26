/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 06:58:31 by amentag           #+#    #+#             */
/*   Updated: 2023/04/14 15:28:17 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc_handler(int sig)
{
	(void)sig;
	g_err_code = 130;
	close(0);
}

int	ft_dup(t_console *console)
{
	int	new_fd;

	new_fd = dup(0);
	if (new_fd == -1)
		return (ft_putstr_fd("dup failed\n", 2), free_console(console, 1), -1);
	return (new_fd);
}

char	*get_content(t_console *console, char *delimiter)
{
	char	*content;
	char	*line;

	content = ft_strdup("");
	console->stdin_copy = ft_dup(console);
	signal(SIGINT, herdoc_handler);
	line = readline(">");
	if (line)
		collect(line);
	while (g_err_code != 130 && line && ft_strcmp(line, delimiter))
	{
		if (g_err_code != -5)
			line = variable_handler_hd(line, console);
		else
			g_err_code = 0;
		content = ft_strjoin(ft_strjoin(content, line), "\n");
		if (!content)
			free_console(console, 1);
		line = readline(">");
		if (line)
			collect(line);
	}
	if (g_err_code == 130)
		return (NULL);
	return (content);
}

void	*herdoc2(t_console *cont, t_heredoc *herdocs, char *delimiter, int n)
{
	if (!delimiter)
		return (free_console(cont, 1), NULL);
	herdocs->delimiter = delimiter;
	herdocs->numero_of_command = n;
	herdocs->content = get_content(cont, delimiter);
	if (!(herdocs->content))
	{
		if (dup2(cont->stdin_copy, STDIN_FILENO) == -1)
			return (ft_putstr_fd("dup2 failed\n", 2), exit(1), NULL);
		close(cont->stdin_copy);
		return (NULL);
	}
	return (herdocs);
}

t_heredoc	*handle_herdoc(char *str, t_console *cont)
{
	t_heredoc	*heredocs;
	int			i;
	int			j;
	int			n;

	heredocs = ft_malloc(cont->nb_herdoc * sizeof(t_heredoc));
	if (!heredocs)
		free_console(cont, 1);
	n = 0;
	i = 0;
	j = 0;
	while (str[i] && g_err_code == 0)
	{
		if (str[i] == '|' && is_valid_pipe(str, i) == 1)
			n++;
		if (str[i] == '<' && valid_hd(str, i) == 1)
		{
			if (!herdoc2(cont, heredocs + j, extract_redir(str, i, '<'), n))
				return (NULL);
			j++;
		}
		else
			i++;
	}
	return (heredocs);
}
