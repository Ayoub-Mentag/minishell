/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 06:43:42 by amentag           #+#    #+#             */
/*   Updated: 2023/04/12 06:56:30 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_trime(char *str, int i)
{
	int	y;

	if (str && str[0] == '\0')
		return ;
	y = i + 1;
	while (str[y])
		str[i++] = str[y++];
	while (str[i])
		str[i++] = '\0';
}

void	ft_rmove_quote(char *str)
{
	int		i;
	char	type_quote;	

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
		{
			g_err_code = -5;
			type_quote = str[i];
			ft_trime(str, i);
			while (str[i] && str[i] != type_quote)
				i++;
			ft_trime(str, i);
		}
		else
			i++;
	}
}

int	count_options(char *line, int end)
{
	int	z;
	int	options;

	z = 0;
	options = 0;
	while (line[z] == ' ' && z < end)
			z++;
	while (z < end)
	{
		if (line[z] != ' ')
		{
			options++;
			while (line[z] && (line[z] != ' ' || check_q(line, z) != 0)
				&& z < end)
				z++;
		}
		else
			z++;
	}
	return (options);
}

int	is_command_build_in(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	else
		return (COMMAND);
}

int	ft_size_cmd(char *str, int end_cmd)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < end_cmd)
	{
		if (str[i] != ' ')
		{
			while (i < end_cmd)
			{
				if (str[i] == ' ' && check_q(str, i) == 0)
					break ;
				else
					i++;
			}
			size++;
		}
		else
			i++;
	}
	return (size);
}
