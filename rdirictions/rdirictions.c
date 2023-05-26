/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirictions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:55:44 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/05 22:55:44 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_up_inredir(char *file, t_console *cont)
{
	if (access(file, F_OK) == -1)
		return (ft_putstr_fd(file, 2), \
				ft_putstr_fd(" No such file or directory\n", 2), 0);
	if (access(file, R_OK) == -1)
		return (ft_putstr_fd("Permission denied\n", 2), 0);
	if (cont->definer->in != 0)
		close(cont->definer->in);
	cont->definer->in = open(file, O_RDONLY);
	if (cont->definer->in == -1)
		return (0);
	return (1);
}

int	check_inredir(char *str, int z, t_console *cont)
{
	char	*file;

	file = extract_redir(str, z, '<');
	if (!file)
		return (-1);
	if (the_last_inredir(str, z) == 1)
		return (set_up_inredir(file, cont));
	return (1);
}

int	handle_outredir(char *str, int spot, t_console *cont)
{
	char	*file;
	int		flag;

	flag = 0;
	if (str[spot + 1] == '>')
		flag = 1;
	file = extract_redir(str, spot, '>');
	if (cont->definer->out != 1)
		close(cont->definer->out);
	if (flag == 1)
	{
		cont->definer->out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else
		cont->definer->out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (cont->definer->out == -1)
	{
		perror("");
		return (0);
	}
	return (1);
}

int	check_redirz(char *str, int end, t_console *cont)
{
	int	i;
	int	r;

	i = 0;
	while (i < end)
	{
		end = find_end_command_2(str, 0);
		if (str[i] == '>' && check_q(str, i) == 0)
		{
			if (handle_outredir(str, i, cont) != 1)
				return (0);
		}
		else if (str[i] == '<' && valid_inredir(str, i) == 1)
		{
			r = check_inredir(str, i, cont);
			if (r == -1)
				free_console(cont, 1);
			if (r != 1)
				return (0);
		}
		else
			i++;
	}
	return (1);
}
