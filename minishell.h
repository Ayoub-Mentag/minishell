/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:04:40 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/03/22 22:03:42 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>

extern int	g_err_code;

# define COMMAND 0
# define EXIT 1
# define ECHO 2
# define ENV 3
# define PWD 4
# define EXPORT 5
# define UNSET 6
# define CD 7
# define ASSIGNED 8
# define NOTASSIGNED 9

typedef struct s_block
{
	void			*block_of_memory;
	struct s_block	*next;
}	t_block;

typedef struct s_node {
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_cmd
{
	char	*path_main_cmd;
	char	*opt_cmd;
}		t_cmds;

typedef struct s_heredoc {
	char		*delimiter;
	int			numero_of_command;
	char		*content;
	int			quote;
}	t_heredoc;

typedef struct s_definer {
	int					type;
	int					in;
	int					out;
	char				**cmds;
	struct s_definer	*next;
}	t_definer;

typedef struct s_env_node
{
	char				*var;
	char				*value;
	struct s_env_node	*next;
	int					index;
	int					type;
}	t_env_node;

typedef struct s_console
{
	t_node			*commands;
	t_heredoc		*heredocs;
	char			current_dir[256];
	int				number_command;
	char			*saved_str;
	char			**env;
	t_env_node		*head_env;
	char			**delemeter;
	int				nb_herdoc;
	t_definer		*definer;
	char			*telda;
	int				exit_code;
	char			*heredoc_file_name;
	int				secure;
	char			*secure_path;
	int				stdin_copy;
}					t_console;
//
void		ft_parsing(char *str, t_console *content, int i);
size_t		ft_strlen(const char *str);
char		*ft_strdup(char *src);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
int			collect(void *alocated);
void		*ft_malloc(size_t size);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(const char *str, char c);
int			error_inredir(char *failed_redir);
int			find_end_command_2(char *str, int i);
int			valid_inredir(char *str, int spot);
int			check_q(char *line, int index);
int			nb_hdocs(char *str);
void		ft_lstadd_front(t_node **lst, t_node *new);
t_heredoc	*handle_herdoc(char *str, t_console *cont);
void		ft_lstadd_back(t_node **lst, t_node *new);
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_node		*ft_lstlast(t_node *lst);
int			check_redirz(char *str, int end, t_console *cont);
int			is_valid_pipe(char *line, int spot);
char		*ft_itoa(int n);
int			check_str(t_console *console, char *str);
void		error_syntax(char *str, int z, int opt);
int			calcule_command(char *str);
int			find_end_command(char *str);
void		handle_sigdoc(int sig);
void		variable_handler(char *str, t_console *content);
int			valid_hd(char *str, int spot);
void		trim_redir(char *line, int spot, int z);
void		execute(t_console *console, int index, int *fd);
void		ft_store_cmd(char *str, int j, t_console *content);
int			count_options(char *line, int end);
int			ft_size_cmd(char *str, int end_cmd);
void		ft_rmove_quote(char *str);
void		open_and_write_to_heredoc(t_console *cont, int numero_of_command);
int			ft_curr_cmd_contains_heredoc(t_console *console, int index);
void		handle_sinagls(void);
void		ft_rest(t_console *cont, char *str);
void		expand_var(int spot, int end_var, t_console *content);
void		replace_var(t_console *content, int spot, int end, char *var);
char		*avoid_quotes(char *line, int spot);
char		*extract_redir(char *line, int spot, char type);
int			the_last_inredir(char *line, int spot);
void		trim_cmd(char *line);
t_env_node	*get_min(t_env_node *head);
int			ft_env_size(t_env_node *head);
void		ft_sort_head_env(t_env_node *head);
char		*ft_sp_strdup(char *s1, char *d);
int			ft_spectial_strlen(char *s, char *dilimiter);
int			is_command_build_in(char *cmd);
char		*ft_expand_var(t_env_node *head_env, char *var);
t_env_node	*ft_copy_env(char *env[]);
void		echo(t_console *console);
void		cd(t_console *console);
void		print_env(t_console *console);
void		print_pwd(t_console *console);
void		export(t_console *console);
void		ft_add_env(char *var, char *value, t_env_node *head);
t_env_node	*exist_in_env_list(t_env_node *head, char *var);
int			ft_env_size(t_env_node *head);
void		unset(char *var_name, t_env_node **head, t_console *console);
void		unset_vars(t_console *console);
void		my_exit(t_console *console);
void		ft_envadd_back(t_env_node **head, t_env_node *new);
void		ft_env_clear(t_env_node **head);
void		print_env_sorted(t_env_node *head);
t_env_node	*get_last_env_node(t_env_node *head);
void		ft_set_index_and_update(t_env_node *head, t_env_node *node);
void		ft_add_env(char *var, char *value, t_env_node *head);
int			check_var_name(char *s);
int			ft_exist_in_str(char c, char *s);
int			ft_spectial_strlen(char *s, char *dilimiter);
void		execute_build_in(t_console *console);
void		write_in_stderror(char *cmd);
void		free_console(t_console *console, int e);
void		handle_sigint(int sig);
void		ft_close(int fd);
char		*return_delimiter(char *str, int spot);
void		prompt_heredocs(t_heredoc *heredocs, t_console *console);
void		free_blocks(t_block **head);
void		free_all(void);
void		init_block(t_block *block, void *alocated);
void		ft_handle_sig(void);
size_t		ft_sk_strlcpy(char *dst, const char *src, int spot);
char		*variable_handler_hd(char *line, t_console *content);
char		*expand_var_hd(int spot, char *line, int end_var, t_console *cont);
char		*rep_var_hd(t_console *cont, char *line, int spots[2], char *var);
int			ft_atoi(char *str);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			get_list_size(t_env_node *head);
void		execute_cmd(t_console *console);
void		execute_multiple_commands(t_console *console, int *fd, int index);
void		error_var(char *s);
void		ft_loop_cmd(t_console *cont, char *str);
void		ft_run(t_console *console, char *str);
char		*get_telda(t_env_node *head_env);

#endif
