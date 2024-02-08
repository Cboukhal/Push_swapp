/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboukhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:51:21 by cboukhal          #+#    #+#             */
/*   Updated: 2024/01/15 12:00:53 by cboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <linux/limits.h>
# include <pwd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

#define MAX_HISTORY_SIZE 50
#define MAX_COMMAND_LENGTH 100

typedef struct		s_env
{
	char			*var;		// var name exemple : PATH
	struct s_env	*next;
}					t_env;

void	dup_env(char **envp);
char	**split(char *raw_cmd, char *limit);
bool	is_built_in(char *cmd);
char	**lst_to_array(void);
char	*get_env_var(char *var);
void	exec_cmd(char **cmd, char **env);
void	free_array(char **array);
void	free_lst(void);
void	exec_built_in(char **built_in);
bool	get_absolute_path(char **cmd, char **env);
void	built_in_cd(char *path);
char	*built_in_pwd(void);
void	add_tail(char *var);
void	add_env_var(char *var);
void	built_in_echo(const char *message);
void	built_in_exit();
void	built_in_export(char *var);
void	built_in_unset(char *var);
void	echo_quote(const char *message);
size_t  my_strlen(const char *str);
int		my_strcmp(const char *str1, const char *str2);
char	*my_strcpy(char *dest, const char *src);
char	*my_strdup(const char *src);
char	*my_strrchr(const char *str, int c);
char	*my_strcat(char *dest, const char *src);
char	*my_strncpy(char *dest, const char *src, size_t n);
int 	my_strncmp(const char *str1, const char *str2, size_t n);
char 	*my_strtok(char *str, const char *delim);
void 	my_putchar(char c);
void	*my_calloc(size_t nmemb, size_t size);
size_t	my_strcspn(const char *str, const char *reject);

# endif
