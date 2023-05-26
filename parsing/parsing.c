/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 02:24:31 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/12 13:13:44 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parsing(char *str, t_console *content, int i)
{
	int		end_cmd;
	int		y;
	char	*check_str;

	variable_handler(str, content);
	if (check_redirz(content->saved_str, \
		find_end_command(content->saved_str), content) != 1)
		return ;
	end_cmd = find_end_command(content->saved_str);
	while (content->saved_str[i] && content->saved_str[i] == 32)
		i++;
	y = i;
	while (content->saved_str[y] && content->saved_str[y] != 32 && \
		content->saved_str[y] != '|')
		y++;
	check_str = ft_substr(content->saved_str, i, y - i);
	if (!check_str)
		free_console(content, 1);
	if (ft_strlen(check_str) == 0)
	{
		content->definer->cmds = NULL;
		return ;
	}
	ft_store_cmd(content->saved_str, end_cmd, content);
}
