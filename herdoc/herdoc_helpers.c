/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:12:12 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/12 12:37:34 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_hd(char *str, int spot)
{
	int	end;

	end = find_end_command_2(str, spot);
	if (str[spot] == '<'
		&& str[spot + 1] == '<'
		&& check_q(str, spot) == 0)
	{
		spot += 2;
		while (spot < end)
		{
			if (str[spot] != ' ')
				return (1);
			spot++;
		}	
	}	
	return (0);
}

int	nb_hdocs(char *str)
{
	int	count;
	int	z;

	z = 0;
	count = 0;
	while (str[z])
	{
		if (str[z] == '<' && valid_hd(str, z) == 1)
			count++;
		z++;
	}
	return (count);
}
