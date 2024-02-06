#include "../include/minishell.h"

bool	is_built_in(char *cmd)
{
	int			i;
	const char	*built_in[] = {"pwd", "cd", "env", "exit",
		"export", "unset", "echo", NULL};

	i = 0;
	while (built_in[i])
	{
		if (!my_strcmp(built_in[i], cmd))
			return (true);
		i++;
	}
	return (false);
}

void	built_in_cd(char *path)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	oldpwd = NULL;
	pwd = NULL;
	pwd_ptr = NULL;
	if (path == NULL)
		return ;
	if (chdir(path) == 0)
	{
		pwd = my_strrchr(get_env_var("PWD="), '=') + 1;
		oldpwd = my_strrchr(get_env_var("OLDPWD="), '=') + 1;
		if (oldpwd != NULL && pwd != NULL)
			my_strcpy(oldpwd, pwd);
		if (pwd != NULL)
		{
			pwd = &pwd[-my_strlen("PWD=")];
			pwd_ptr = built_in_pwd();
			my_strcpy(pwd, pwd_ptr);
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	}
	else
		perror("chdir");
}

char	*built_in_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = (char *)calloc(sizeof(char), PATH_MAX + my_strlen("PWD=") + 1);
	if (cwd == NULL)
		return (NULL);
	my_strcat(cwd, "PWD=");
	if (getcwd(&cwd[4], PATH_MAX) == NULL)
		perror("getcwd()");
	return (cwd);
}

void	built_in_exit(void)
{
	printf("Bye ! Exiting the shell...\n");
	exit(EXIT_SUCCESS);
}
