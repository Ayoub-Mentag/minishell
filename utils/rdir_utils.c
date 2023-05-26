/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:04:29 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/04/14 02:19:04 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*avoid_quotes(char *line, int spot)
{
	int		end;
	int		z;
	char	*extract;

	z = 0;
	spot++;
	end = spot;
	while (line[end] && (line[end] != ' ' && check_q(line, end) != 0))
		end++;
	extract = ft_malloc ((end - spot + 1) * sizeof(char));
	while (extract && spot < end)
	{
		extract[z] = line[spot];
		z++;
		spot++;
	}
	return (extract);
}

int	is_valid_rdir(char *line, int spot)
{
	if ((line[spot] == '<' || line[spot] == '>') && check_q(line, spot) == 0)
		return (1);
	return (0);
}

char	*extract_redir(char *line, int spot, char type)
{
	char	*new_line;
	int		y;
	int		i;

	i = spot;
	while (line[spot] && (line[spot] == ' ' || line[spot] == type))
		spot++;
	y = spot;
	while (line[y] && (line[y] != ' ' || check_q(line, y) != 0) && \
	is_valid_pipe(line, y) != 1 && is_valid_rdir(line, y) != 1)
		y++;
	new_line = ft_substr(line, spot, y - spot);
	ft_rmove_quote(new_line);
	trim_redir(line, i, y);
	return (new_line);
}

void	trim_redir(char *line, int spot, int z)
{
	while (line[z])
	{
		line[spot] = line[z];
		spot++;
		z++;
	}
	while (line[spot])
	{
		line[spot] = '\0';
		spot++;
	}
}

int	the_last_inredir(char *line, int spot)
{
	int	end;

	spot++;
	end = find_end_command_2(line, spot);
	while (spot < end)
	{
		if (line[spot] == '<' && valid_inredir(line, spot) == 1)
			return (0);
		spot++;
	}
	return (1);
}
