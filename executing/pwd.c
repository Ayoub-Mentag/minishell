/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:40:04 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:40:04 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_pwd(t_console *console)
{
	int	out;
	int	len;

	out = console->definer->out;
	getcwd(console->current_dir, sizeof(console->current_dir));
	len = ft_strlen(console->current_dir);
	write(out, console->current_dir, len);
	write(out, "\n", 1);
}
