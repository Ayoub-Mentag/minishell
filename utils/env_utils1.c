/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:45:59 by amentag           #+#    #+#             */
/*   Updated: 2023/04/07 15:45:59 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_node	*exist_in_env_list(t_env_node *head, char *var)
{
	t_env_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_expand_var(t_env_node *head_env, char *var)
{
	while (head_env)
	{
		if (ft_strcmp(head_env->var, var) == 0)
			return (head_env->value);
		head_env = head_env->next;
	}
	return (NULL);
}

t_env_node	*init_node_helper(t_env_node *new_env)
{
	int	shlvl;

	if (new_env->value)
	{
		shlvl = ft_atoi(new_env->value);
		free(new_env->value);
		if (shlvl >= 999)
		{
			if (shlvl == 999)
				new_env->value = ft_sp_strdup("", "");
			else
			{
				printf("bash: warning: shell level (%d)\
				too high, resetting to 1\n", shlvl);
				new_env->value = ft_sp_strdup("1", "");
			}
		}	
		else
			new_env->value = ft_sp_strdup(ft_itoa(shlvl + 1), "");
		if (!new_env->value)
			return (NULL);
	}
	return (new_env);
}

t_env_node	*init_node(char *tmp)
{
	t_env_node	*new_env;

	new_env = malloc(sizeof(t_env_node));
	if (!new_env)
		return (NULL);
	new_env->index = -1;
	new_env->type = ASSIGNED;
	new_env->var = ft_sp_strdup(tmp, "=");
	new_env->next = NULL;
	tmp += ft_spectial_strlen(tmp, "=") + 1;
	new_env->value = ft_sp_strdup(tmp, "");
	if (new_env && ft_strcmp(new_env->var, "SHLVL") == 0)
		return (init_node_helper(new_env));
	if (!new_env->value || !new_env->var)
		return (NULL);
	return (new_env);
}

t_env_node	*ft_copy_env(char *env[])
{
	t_env_node	*head_env;
	t_env_node	*new_env;
	char		*tmp;
	int			i;

	i = 0;
	head_env = NULL;
	tmp = env[i];
	while (tmp)
	{
		new_env = init_node(tmp);
		if (!new_env)
			return (NULL);
		tmp = env[++i];
		ft_envadd_back(&head_env, new_env);
	}
	return (head_env);
}
