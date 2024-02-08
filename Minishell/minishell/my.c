#include "../include/minishell.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void *my_calloc(size_t nmemb, size_t size)
{
    size_t total_size;
    void *ptr;
    size_t i;

    if (nmemb == 0 || size == 0)
        return NULL;
    total_size = nmemb * size;
    ptr = malloc(total_size);
    if (ptr == NULL)
        return NULL;
    i = 0;
    while (i < total_size)
    {
        ((char *)ptr)[i] = 0;
        i++;
    }
    return ptr;
}
