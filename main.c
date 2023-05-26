/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:47:24 by amentag           #+#    #+#             */
/*   Updated: 2023/04/14 02:47:24 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_err_code = 0;

t_env_node	*ft_get_node(char *var, char *value)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return (NULL);
	var = ft_sp_strdup(var, "");
	if (!var)
		return (NULL);
	value = ft_sp_strdup(value, "");
	if (!value)
		return (NULL);
	node->var = var;
	node->value = value;
	node->next = NULL;
	node->index = -1;
	node->type = ASSIGNED;
	return (node);
}

t_env_node	*ft_copy_i_env(char *current)
{
	t_env_node	*head;
	t_env_node	*node;

	head = NULL;
	node = ft_get_node("PWD", current);
	if (!node)
		return (NULL);
	ft_envadd_back(&head, node);
	node = ft_get_node("SHLVL", "1");
	if (!node)
		return (NULL);
	ft_envadd_back(&head, node);
	node = ft_get_node("_", "/usr/bin/env");
	if (!node)
		return (NULL);
	ft_envadd_back(&head, node);
	return (head);
}

void	init_head_env(t_console *con, char **env)
{
	if (!env[0])
	{
		con->secure = 1;
		con->secure_path = \
		ft_sp_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", "");
		con->head_env = ft_copy_i_env(con->current_dir);
	}
	else
		con->head_env = ft_copy_env(env);
	if (!con->head_env)
		return (ft_env_clear(&(con->head_env)), free(con), exit(1));
	ft_sort_head_env(con->head_env);
}

t_console	*initial(char **env)
{
	t_console	*con;

	con = malloc(sizeof(t_console));
	if (!con)
		exit(1);
	con->heredoc_file_name = NULL;
	con->secure_path = NULL;
	con->secure = 0;
	con->commands = NULL;
	getcwd(con->current_dir, sizeof(con->current_dir));
	init_head_env(con, env);
	con->definer = malloc(sizeof(t_definer));
	if (!con->definer)
		return (ft_env_clear(&(con->head_env)), free(con), exit(1), NULL);
	con->definer->in = 0;
	con->definer->out = 1;
	con->env = env;
	con->telda = get_telda(con->head_env);
	if (!con->telda)
		return (ft_env_clear(&(con->head_env)), free(con->definer), \
		free(con), exit(1), NULL);
	con->exit_code = 0;
	con->heredoc_file_name = NULL;
	return (con);
}

int	main(int ac, char **av, char **env)
{
	t_console	*console;
	char		*str;

	(void)ac;
	(void)av;
	console = initial(env);
	while (1)
	{
		ft_handle_sig();
		rl_catch_signals = 0;
		str = readline("minishell >> ");
		console->exit_code = g_err_code;
		g_err_code = 0;
		collect(str);
		if (!str)
			free_console(console, 0);
		if (str[0] != '\0')
			add_history(str);
		ft_run(console, str);
	}
}
