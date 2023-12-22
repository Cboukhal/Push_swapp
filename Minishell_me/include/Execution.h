#ifndef EXECUTION_H
# define EXECUTION_H

# include <pthread.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <pwd.h>
#include <sys/types.h>

char	**split(char *raw_cmd, char *limit);
void	exec_cmd(char **cmd);
void	free_array(char **array);
char *my_strdup(const char *src);
void	get_absolute_path(char **cmd);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

# endif