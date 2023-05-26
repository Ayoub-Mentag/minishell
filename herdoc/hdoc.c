/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 07:07:45 by amentag           #+#    #+#             */
/*   Updated: 2023/04/08 07:07:45 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*generate_file_name(void)
{
	static int	i;
	char		*file_name;

	file_name = ft_strjoin(".", ft_itoa(i));
	while (file_name && access(file_name, X_OK) == 0)
	{
		i++;
		file_name = ft_strjoin(".", ft_itoa(i));
	}
	return (file_name);
}

int	ft_curr_cmd_contains_heredoc(t_console *console, int index)
{
	int	i;

	i = 0;
	while (i < console->nb_herdoc)
	{
		if (console->heredocs[i].numero_of_command == index)
			return (1);
		i++;
	}
	return (0);
}

void	write_to_heredoc_file(int fd, char *value)
{
	write(fd, value, ft_strlen(value));
	write(fd, "\n", 1);
}

void	open_and_write_to_heredoc(t_console *cont, int numero_of_command)
{
	int		fd;
	int		z;

	z = 0;
	cont->heredoc_file_name = generate_file_name();
	if (!cont->heredoc_file_name)
		free_console(cont, 1);
	fd = open(cont->heredoc_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (cont->heredocs[z].numero_of_command != numero_of_command)
		z++;
	while (z < cont->nb_herdoc && \
		cont->heredocs[z].numero_of_command == numero_of_command)
		z++;
	z--;
	if (z < cont->nb_herdoc)
	{
		ft_putstr_fd(cont->heredocs[z].content, fd);
		close(fd);
		fd = open(cont->heredoc_file_name, O_RDONLY, 0777);
		if (cont->definer->in != 0)
			close(cont->definer->in);
		cont->definer->in = fd;
	}	
}
