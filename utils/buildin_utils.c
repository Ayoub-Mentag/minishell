/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:08:57 by amentag           #+#    #+#             */
/*   Updated: 2023/04/11 23:19:12 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_vars(t_console *console)
{
	int		i;
	char	*var_name;

	i = 1;
	var_name = console->definer->cmds[i];
	while (var_name)
	{
		unset(var_name, &(console->head_env), console);
		i++;
		var_name = console->definer->cmds[i];
	}
}
