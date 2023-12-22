#ifndef EXECUTION_H
# define EXECUTION_H

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
#include <readline/readline.h>
#include <readline/history.h>

int     custom_strlen   (const char *str);
int     custom_strcmp(const char *str1, const char *str2);
int     custom_strncmp(const char *str1, const char *str2, size_t n);
char    *custom_strrchr(const char *str, int character);
char    *custom_strcpy(char *dest, const char *src);
void    *my_calloc(size_t num_elements, size_t element_size);
void    *custom_realloc(void *ptr, size_t new_size);
char    *custom_strtok(char *str, const char *delim);
char    *custom_strdup(const char *str);
char    *custom_strcat(char *dest, const char *src);

# endif