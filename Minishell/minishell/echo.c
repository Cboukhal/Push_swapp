#include "../include/minishell.h"

int	simple_quote(const char *ptr)
{
	if (ptr[0] == 39 && ptr[my_strlen(ptr)-1] == 39)
		return (0);
	return (1);
}

int	double_quote(const char *ptr)
{
	if (ptr[0] == 34 && ptr[my_strlen(ptr)-1] == 34)
		return (0);
	return (1);
}

int my_isalnum(int c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void	built_in_echo(const char *message)
{
	const char	*start;
	const char	*ptr;
	char		*var_value;
	char		*var_name;
	size_t		var_len;

	if (message == NULL)
	{
		printf("\n");
        return;
	}
	ptr = message;
	while (*ptr != '\0')
	{
		if (!simple_quote (ptr))
		{
			//++ptr;
			start = ++ptr;
			while (*ptr != 39)
			{
				my_putchar(*ptr);
				++ptr;
			}
			++ptr;
		}
		if (!double_quote(ptr))
			++ptr;
		if (*ptr == '$')
		{
			start = ++ptr;
			while (my_isalnum(*ptr) || *ptr == '_')
				++ptr;
			var_len = ptr - start;
			var_name = (char *)my_calloc(var_len + 1, sizeof(char));
			if (var_name == NULL)
			{
				perror("Allocation error");
				return;
			}
			my_strncpy(var_name, start, var_len);
			var_name[var_len] = '\0';
			var_value = get_env_var(var_name);
			if (var_value != NULL)
				printf("%s", var_value);
			else
				printf("$%s", var_name);
			free (var_name);
		}
		else
		{
			putchar (*ptr);
			++ptr;
		}
	}
}
