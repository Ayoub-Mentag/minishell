/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_hd_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:36:52 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/11 23:44:01 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rep_var_hd(t_console *cont, char *line, int spots[2], char *var)
{
	char	*ante;
	char	*pre;
	int		len;

	len = ft_strlen(line);
	ante = ft_substr(line, 0, spots[0]);
	pre = ft_substr(line, spots[1], len - spots[1]);
	if (!ante || !pre)
		free_console(cont, 1);
	line = ft_strjoin(ante, var);
	line = ft_strjoin(line, pre);
	if (!line)
		free_console(cont, 1);
	return (line);
}

static void	m_trim_hd(char *str, int start, int end)
{
	end++;
	if (!str && str[0] == '\0')
		return ;
	while (str[end])
	{
		str[start] = str[end];
		start++;
		end++;
	}
	while (str[start])
	{
		str[start] = '\0';
		start++;
	}
}

char	*expand_var_hd(int spot, char *line, int end_var, t_console *cont)
{
	char	*var_val;
	char	*var;
	int		x;
	int		spots[2];

	x = end_var - (spot + 1);
	var = ft_substr(line, spot + 1, x);
	if (!var)
		free_console(cont, 1);
	var_val = ft_expand_var(cont->head_env, var);
	if (!var_val)
	{
		m_trim_hd(line, spot, end_var - 1);
	}
	else
	{
		spots[0] = spot;
		spots[1] = end_var;
		line = rep_var_hd(cont, line, spots, var_val);
	}
	return (line);
}
