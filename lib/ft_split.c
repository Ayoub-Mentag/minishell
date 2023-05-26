/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:01:15 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/03/22 22:01:16 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	words_count(const char *str, char c)
{
	int	x;
	int	i;
	int	index;

	index = 0;
	i = 0;
	x = 0;
	while (str[index])
	{
		if (str[index] != c && x == 0)
		{
			x = 1;
			i++;
		}
		else if (str[index] == c)
			x = 0;
		index++;
	}
	return (i);
}

static void	handle_word(char *dest, const char *new_word, char c)
{
	int	i;

	i = 0;
	while (new_word[i] && new_word[i] != c)
	{
		dest[i] = new_word[i];
		i++;
	}
	dest[i] = '\0';
}

static int	fill_array(char **split, const char *str, char c)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\0' || str[i] == c)
			i++;
		else
		{
			j = 0;
			while ((str[i + j] == c || str[i + j] == '\0') == 0)
				j++;
			split[word] = ft_malloc(sizeof(char) * (j + 1));
			if (!split[word])
				return (-1);
			handle_word(split[word], str + i, c);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**ft_split(const char *str, char c)
{
	char	**res;
	int		words;

	if (!str)
		return (NULL);
	words = words_count(str, c);
	res = ft_malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (0);
	res[words] = 0;
	if (fill_array(res, str, c) == -1)
		return (NULL);
	return (res);
}
