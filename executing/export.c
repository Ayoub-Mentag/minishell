/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:36:39 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:36:39 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	dest = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	free(s2);
	return (dest);
}

void	export_helper(char *var, char *value, t_env_node *head, char join)
{
	t_env_node	*node;

	node = exist_in_env_list(head, var);
	if (node)
	{
		free(var);
		node->type = ASSIGNED;
		if (join == '+' && node->value)
			node->value = ft_join(node->value, value);
		else
		{
			if (node->value)
				free(node->value);
			if (!value)
				node->type = NOTASSIGNED;
			node->value = value;
		}
	}
	else
		ft_add_env(var, value, head);
}

void	export(t_console *console)
{
	int		i;
	int		len;
	char	*value;
	char	*var;

	i = 1;
	if (!console->definer->cmds[i])
		return (print_env_sorted(console->head_env));
	while (console->definer->cmds[i])
	{
		value = NULL;
		if (!check_var_name(console->definer->cmds[i]))
			return ;
		len = ft_spectial_strlen(console->definer->cmds[i], "+=");
		var = ft_sp_strdup(console->definer->cmds[i], "+=");
		if (ft_strcmp(var, "PATH") == 0)
			console->secure = 0;
		if (console->definer->cmds[i][len] == '=' || \
				console->definer->cmds[i][len] == '+')
			value = ft_sp_strdup(console->definer->cmds[i] + \
			ft_spectial_strlen(console->definer->cmds[i], "=") + 1, "");
		export_helper(var, value, console->head_env, \
		console->definer->cmds[i][len]);
		i++;
	}
}
