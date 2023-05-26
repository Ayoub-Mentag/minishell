/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:47:07 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/11 22:14:56 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_q(char *line, int index)
{
	int		i;
	char	type_quote;

	i = 0;
	while (i < index)
	{
		if (line[i] == 39 || line[i] == 34)
		{
			type_quote = line[i];
			i++;
			while (line[i] && line[i] != type_quote)
				i++;
		}
		if (i > index && line[i] == 34)
			return (1);
		else if (i > index && line[i] == 39)
			return (2);
		i++;
	}
	return (0);
}

int	is_valid_pipe(char *line, int spot)
{
	if (line[spot] == '|'
		&& check_q(line, spot) == 0)
		return (1);
	return (0);
}

int	valid_inredir(char *str, int spot)
{
	int	end;

	end = find_end_command_2(str, spot);
	if (spot != 0)
	{
		if (str[spot - 1] == '<')
			return (0);
	}
	if (check_q(str, spot) != 0
		|| str[spot + 1] == '<')
		return (0);
	while (spot < end)
	{
		if (str[spot] != ' ')
			return (1);
		spot++;
	}
	return (0);
}

void	ft_rest(t_console *cont, char *str)
{
	cont->definer->cmds = NULL;
	cont->definer->in = 0;
	cont->definer->out = 1;
	cont->heredoc_file_name = NULL;
	trim_cmd(str);
}
