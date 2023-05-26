/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 06:47:32 by amentag           #+#    #+#             */
/*   Updated: 2023/04/08 06:47:32 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_syntax(char *str, int z, int opt)
{
	char	err_char;

	err_char = str[z];
	g_err_code = 258;
	ft_putstr_fd(" syntax error near unexpected token `", 2);
	if (err_char == '\0' && opt != 2)
		ft_putstr_fd("newline", 2);
	else
	{	
		while (str[z] && str[z] == err_char)
		{
			write(2, &err_char, 1);
			z++;
		}
	}
	ft_putstr_fd("\n", 2);
}

void	error_var(char *s)
{
	ft_putstr_fd("Invalid identifier ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(".\n", 2);
}
