#include "../include/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	exec_cmd(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, env) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

bool	get_absolute_path(char **cmd, char **env)
{
	char	*path;
	char	*bin;
	char	**path_split;
	size_t	idx;
	int		i;

	i = 0;
	path = NULL;
	bin = NULL;
	path_split = NULL;
	idx = 0;
	if (cmd[0][0] != '/' && my_strncmp(cmd[0], "./", 2) != 0)
	{
		while (env[i])
		{
			if (!my_strncmp(env[i], "PATH=", 5))
			{
				path = my_strdup(&env[i][5]);
				break ;
			}
			i++;
		}
		if (path == NULL)
			return (false);
		path_split = split(path, ":");
		free(path);
		path = NULL;
		idx = 0;
		while (path_split[idx])
		{
			bin = (char *)calloc(sizeof(char),(my_strlen(path_split[idx]) + 1 + my_strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;
			my_strcat(bin, path_split[idx]);
			my_strcat(bin, "/");
			my_strcat(bin, cmd[0]);
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
			idx++;
		}
		free_array(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
	return (bin == NULL ? false : true);
}

void	add_env_var(char *var)
{
	struct passwd	*pw;
	char			*alloc;

	pw = getpwuid(getuid());
	alloc = NULL;
	if (!my_strcmp(var, "HOME"))
	{
		alloc = (char *)calloc(sizeof(char), my_strlen(pw->pw_dir) + my_strlen("HOME=") + 1);
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add HOME\n");
			return ;
		}
		my_strcat(alloc, "HOME=");
		my_strcat(alloc, pw->pw_dir);
	}
	else if (!my_strcmp(var, "PATH"))
	{
		alloc = my_strdup("PATH=/bin:/usr/bin");
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add PATH\n");
			return ;
		}
	}
	else if (!my_strcmp(var, "OLDPWD"))
	{
		alloc = my_strdup("OLDPWD=");
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add OLDPWD\n");
			return ;
		}
	}
	else if (!my_strcmp(var, "PWD"))
	{
		alloc = built_in_pwd();
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add PWD\n");
			return ;
		}
	}
	else if (!my_strcmp(var, "SHLVL"))
	{
		alloc = my_strdup("SHLVL=1");
		if (alloc == NULL)
		{
			fprintf(stderr, "Cannot add OLDPWD\n");
			return ;
		}
	}
	add_tail(alloc);
}

char	**split(char *raw_cmd, char *limit)
{
	char	*ptr;
	char	**cmd;
	size_t	idx;
	int		inside_quotes;

	ptr = NULL;
	cmd = NULL;
	idx = 0;
	inside_quotes = 0;
	ptr = my_strtok(raw_cmd, limit);
	while (ptr)
	{
		cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
		cmd[idx] = my_strdup(ptr);
		if (ptr[0] == '\'' || ptr[0] == '\"')
		{
			if (inside_quotes)
				inside_quotes = 0;
			else
				inside_quotes = 1;
		}
		while (inside_quotes && (ptr = my_strtok(NULL, limit)) != NULL)
		{
			my_strcat(cmd[idx], " ");
			my_strcat(cmd[idx], ptr);
		}
		ptr = my_strtok(NULL, limit);
		++idx;
	}
	cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
	cmd[idx] = NULL;
	return (cmd);
}

