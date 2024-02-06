#include "../include/minishell.h"

//static char *history[MAX_HISTORY_SIZE];
//static int history_count = 0;

/*static void print_history()
{
    for (int i = 0; i < history_count; ++i)
    {
        printf("%d: %s\n", i + 1, history[i]);
    }
}*/

static void	free_history(void)
{
	int	i;
	static char *history[MAX_HISTORY_SIZE];
	int	history_count;

	i = 0;
	history_count = 0;
	while (i < history_count)
	{
		free(history[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*buffer;
	size_t	buf_size;
	char	**cmd;
	char	**env;

	buffer = NULL;
	buf_size = 2048;
	cmd = NULL;
	env = NULL;
	dup_env(envp);
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}
	while ((buffer = readline("$> ")) != NULL)
	{
		add_history (buffer);
		cmd = split(buffer, " \n\t");
		if (cmd[0] == NULL)
			fprintf(stderr, "Command not found\n");
		else if (is_built_in(cmd[0]) == true)
			exec_built_in(cmd);
		else
		{
			env = lst_to_array();
			if (get_absolute_path(cmd, env) == true)
				exec_cmd(cmd, env);
			else
				fprintf(stderr, "Command not found\n");
			free(env);
			env = NULL;
		}
		free_array(cmd);
		free(buffer);
	}
	free_history ();
	free_lst();
	printf("Bye \n");
	(void)argc;
	(void)argv;
	return (0);
}
