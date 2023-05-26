/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:03:52 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/10 01:36:08 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_var(t_console *content, int spot, int end, char *var)
{
	char	*ante;
	char	*pre;
	int		len;

	len = ft_strlen(content->saved_str);
	ante = ft_substr(content->saved_str, 0, spot);
	pre = ft_substr(content->saved_str, end, len - end);
	if (!ante || !pre)
		free_console(content, 1);
	content->saved_str = ft_strjoin(ante, var);
	content->saved_str = ft_strjoin(content->saved_str, pre);
	if (!content->saved_str)
		free_console(content, 1);
}

static void	m_trim(char *str, int start, int end)
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

void	expand_var(int spot, int end_var, t_console *content)
{
	char	*var_val;
	char	*var;
	int		x;

	x = end_var - (spot + 1);
	var = ft_substr(content->saved_str, spot + 1, x);
	if (!var)
		free_console(content, 1);
	if (ft_strcmp(var, "PATH") == 0 && content->secure == 1)
		var_val = content->secure_path;
	else
		var_val = ft_expand_var(content->head_env, var);
	if (!var_val)
	{
		m_trim(content->saved_str, spot, end_var - 1);
	}
	else
	{
		replace_var(content, spot, end_var, var_val);
	}
}
