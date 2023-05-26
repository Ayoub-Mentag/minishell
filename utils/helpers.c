/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:41:48 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/03/20 15:55:12 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_end_command(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '|' || is_valid_pipe(str, i) != 1))
		i++;
	return (i);
}

int	calcule_command(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (str == NULL)
		return (x);
	while (str[i])
	{
		if (str[i] == '|' && is_valid_pipe(str, i) == 1)
			x++;
		i++;
	}
	return (x + 1);
}

void	handle_sigdoc(int sig)
{
	if (sig == SIGINT)
	{
		putchar('\n');
		close(STDIN_FILENO);
		g_err_code = -1;
	}
}

int	find_end_command_2(char *str, int i)
{
	while (str[i] && (str[i] != '|' || is_valid_pipe(str, i) != 1))
		i++;
	return (i);
}
