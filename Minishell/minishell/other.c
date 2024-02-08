#include "../include/minishell.h"

char	*built_in_pwd(void);

// First elem dans la liste chainee
t_env	*first = NULL;

char	*get_env_var(char *var)
{
	t_env	*tmp;
	size_t	len;

	tmp = first;
	len = 0;
	len = my_strlen(var);
	while (tmp)
	{
		if (!my_strncmp(var, tmp->var, len))
			return (tmp->var);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	built_in_env(void)
{
	t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	add_tail(char *var)
{
	t_env	*ptr;
	t_env	*new_node;

	ptr = first;
	new_node = NULL;
	new_node = (t_env *)my_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
	{
		printf("Alloc failure\n");
		return ;
	}
	new_node->var = my_strdup(var);
	new_node->next = NULL;
	if (ptr == NULL)
		first = new_node;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

void	echo(char **built)
{
	int		i;
	bool	no_newline;

	i = 1;
	if (i < 2 && my_strcmp(built[i], "-n") == 0)
	{
		no_newline = true;
		i++;
	}
	while (built[i])
	{
		built_in_echo(built[i]);
		if (built[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!no_newline)
		putchar('\n');
}

void	exec_built_in(char **built_in)
{	
	if (!my_strcmp(built_in[0], "pwd"))
		printf("%s\n", get_env_var("PWD="));
	else if (!my_strcmp(built_in[0], "cd"))
		built_in_cd(built_in[1]);
	else if (!my_strcmp(built_in[0], "env"))
		built_in_env();
	else if (!my_strcmp(built_in[0], "exit"))
		built_in_exit();
	else if (!my_strcmp(built_in[0], "echo"))
		echo(built_in);
	else if (!my_strcmp(built_in[0], "unset"))
		built_in_unset(built_in[1]);
	else if (!my_strcmp(built_in[0], "export"))
		built_in_export(built_in[1]);
}

void	dup_env(char **envp)
{
	char	*var_lst[] = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
	ssize_t	nb_elem = 5; // nombre d'element dasn var_lst
	int		i;

	// boucle sur l'env et stock les variables dans la liste
	i = 0;
	while (envp[i])
	{
		add_tail(my_strdup(envp[i]));
		// On verifie que l'on a les variables d'environment minimal
		if (!my_strncmp(envp[i], "PATH", 4)) var_lst[0] = NULL;
		else if (!my_strncmp(envp[i], "HOME", 4)) var_lst[1] = NULL;
		else if (!my_strncmp(envp[i], "OLDPWD", 6)) var_lst[2] = NULL;
		else if (!my_strncmp(envp[i], "PWD", 3)) var_lst[3] = NULL;
		else if (!my_strncmp(envp[i], "SHLVL", 5)) var_lst[4] = NULL;
		i++;
	}

	// On verifie qu l'on a les varaibles PATH, HOME, OLD_PWD et SHLVL
	// sinon on l'ajoute
	i = 0;
	while (i < nb_elem)
	{
		if (var_lst[i] != NULL)
			add_env_var(var_lst[i]);
		i++;
	}
}

char	**lst_to_array(void)
{
	char	**array;
	t_env	*tmp;
	size_t	idx;

	array = NULL;
	tmp = first;
	idx = 0;
	while (tmp)
	{
		idx++;
		tmp = tmp->next;
	}
	array = (char **)my_calloc(sizeof(char *), idx + 1);
	if (array == NULL)
	{
		perror("calloc");
		exit(-1);
	}
	tmp = first;
	idx = 0;
	while (tmp)
	{
		array[idx] = tmp->var;
		tmp = tmp->next;
		idx++;
	}
	return (array);
}

void	free_lst(void)
{
	t_env	*idx;
	t_env	*tmp;

	idx = first;
	tmp = idx;
	while (idx != NULL)
	{
		tmp = idx;
		idx = idx->next;
		free(tmp->var);
		tmp->var = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	built_in_unset(char *var)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = first;
	while (curr)
	{
		if (!my_strcmp(curr->var, var))
		{
			if (prev == NULL)
				first = curr->next;
			else
				prev->next = curr->next;
			free(curr->var);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	built_in_export(char *var)
{
	char	*existing_var;

	existing_var = get_env_var(var);
	if (existing_var != NULL)
	{
		free(existing_var);
		built_in_unset(var);
	}
	add_tail(my_strdup(var));
}
