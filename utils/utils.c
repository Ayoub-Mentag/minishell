/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:53:45 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:53:45 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exist_in_str(char c, char *s)
{
	while (s && *s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

int	ft_spectial_strlen(char *s, char *dilimiter)
{
	int	i;

	i = 0;
	while (s[i] && !ft_exist_in_str(s[i], dilimiter))
		i++;
	return (i);
}

char	*ft_sp_strdup(char *s1, char *d)
{
	char	*result;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_spectial_strlen(s1, d);
	result = malloc(i + 1 * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, i + 1);
	return (result);
}

void	free_console(t_console *console, int e)
{
	free(console->telda);
	ft_env_clear(&(console->head_env));
	free(console->definer);
	free(console->secure_path);
	free(console);
	g_err_code = e;
	exit(e);
}

void	ft_close(int fd)
{
	if (fd > 0)
	{
		close(fd);
	}
}
