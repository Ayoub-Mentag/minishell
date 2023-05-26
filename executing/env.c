/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:27:37 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:27:37 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_console *console)
{
	t_env_node	*head;
	int			out;

	out = console->definer->out;
	head = console->head_env;
	g_err_code = 0;
	while (head)
	{
		if (head->type == ASSIGNED)
		{
			write(out, head->var, ft_spectial_strlen(head->var, ""));
			write(out, "=", 1);
			write(out, head->value, ft_spectial_strlen(head->value, ""));
			write(out, "\n", 1);
		}
		head = head->next;
	}
}
