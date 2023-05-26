/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:39:01 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/12 12:35:47 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*variable_handler_hd(char *line, t_console *content)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			z = i + 1;
			while (line[z] && line[z] != ' ' && line[z] != '$')
				z++;
			line = expand_var_hd(i, line, z, content);
		}
		i++;
	}
	return (line);
}
