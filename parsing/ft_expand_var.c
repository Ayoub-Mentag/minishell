/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:51:23 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/03/20 16:02:14 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_telda(int spot, int end_var, t_console *content)
{
	char	*var_val;

	var_val = content->telda;
	replace_var(content, spot, end_var, var_val);
}

void	sub_err_code(t_console *cont, int spot)
{
	int		z;
	char	*ante;
	char	*pre;
	char	*error;

	z = spot + 1;
	while (cont->saved_str[z] && (ft_isalpha(cont->saved_str[z]) \
		|| ft_isdigit(cont->saved_str[z]) || cont->saved_str[z] == '_'))
		z++;
	error = ft_itoa(cont->exit_code);
	if (!error)
		free_console(cont, 1);
	ante = ft_substr(cont->saved_str, 0, spot - 1);
	pre = ft_substr(cont->saved_str, spot + 1, z - (spot + 2));
	cont->saved_str = ft_strjoin(ante, error);
	cont->saved_str = ft_strjoin(cont->saved_str, pre);
	if (!ante || !pre || !cont->saved_str)
		free_console(cont, 1);
}

static int	check_telda(int spot, t_console *content)
{
	int	z;

	z = spot + 1;
	if ((content->saved_str[spot] == '~') && !check_q(content->saved_str, z) && \
	(content->saved_str[spot + 1] == 32 || content->saved_str[spot + 1] == '\0'\
	|| content->saved_str[spot + 1] == '/'))
		return (expand_telda(spot, z, content), 2);
	return (0);
}

static int	check_variable(int end, int spot, t_console *content)
{
	int	z;

	z = spot + 1;
	if (content->saved_str[spot] == '$' && check_q(content->saved_str, z) != 2)
	{
		if (content->saved_str[z] == ' ' || content->saved_str[z] == 34 || \
		content->saved_str[z] == 39 || content->saved_str[z] == '\0' \
		|| is_valid_pipe(content->saved_str, z) == 1)
			return (0);
		if (content->saved_str[z] == '?')
			sub_err_code(content, z);
		else
		{
			while (z < end && (ft_isalpha(content->saved_str[z]) \
				|| ft_isdigit(content->saved_str[z]) || \
				content->saved_str[z] == '_'))
				z++;
			expand_var(spot, z, content);
		}
		return (1);
	}
	return (check_telda(spot, content));
}

void	variable_handler(char *str, t_console *content)
{
	int	i;
	int	end_cmd;

	i = 0;
	end_cmd = find_end_command(str);
	content->saved_str = str;
	while (i < end_cmd)
	{
		if (check_variable(end_cmd, i, content) != 1)
			i++;
		end_cmd = find_end_command(content->saved_str);
	}
}
