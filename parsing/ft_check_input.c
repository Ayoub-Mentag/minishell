/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:05:42 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/03/22 21:54:43 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_syntax_redir(char *str, char to_check)
{
	int	i;

	i = 0;
	while (str[i] && g_err_code == 0)
	{
		if (str[i] == to_check && check_q(str, i) == 0)
		{
			if (str[i + 1] == to_check)
				i++;
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '<' || str[i] == '>' || is_valid_pipe(str, i) == 1
				|| str[i] == '\0')
				error_syntax(str, i, 1);
		}
		i++;
	}
}

static void	check_syntax_pipes(char *str)
{
	int	z;
	int	y;

	z = 0;
	while (str[z])
	{
		if (is_valid_pipe(str, z) == 1)
		{
			y = z - 1;
			while (y > 0 && str[y] == ' ')
				y--;
			if (y < 0)
			{
				error_syntax(str, z, 2);
				return ;
			}
			y = z + 1;
			while (str[y] && str[y] == ' ')
				y++;
			if (str[y] == '\0' || is_valid_pipe(str, y) == 1)
				return (error_syntax(str, z, 2));
		}
		z++;
	}
}

void	handle_is_close_quotes(char *str)
{
	int		z;
	char	type_quote;

	z = 0;
	while (str[z])
	{
		if (str[z] == 34 || str[z] == 39)
		{
			type_quote = str[z];
			z++;
			while (str[z] && str[z] != type_quote)
				z++ ;
		}
		if (str[z] == '\0')
		{
			ft_putstr_fd("Error : unclosed quotes\n", 2);
			g_err_code = 258;
		}
		else
			z++;
	}
}

int	check_str(t_console *console, char *str)
{
	t_heredoc	*heredocs;

	handle_is_close_quotes(str);
	if (g_err_code == 0)
	{
		check_syntax_pipes(str);
	}
	if (g_err_code == 0)
		check_syntax_redir(str, '<');
	if (g_err_code == 0)
		check_syntax_redir(str, '>');
	if (g_err_code == 0)
	{
		console->nb_herdoc = nb_hdocs(str);
		if (console->nb_herdoc != 0)
		{
			heredocs = handle_herdoc(str, console);
			if (!heredocs)
				return (0);
			console->heredocs = heredocs;
		}
	}
	return (1);
}
