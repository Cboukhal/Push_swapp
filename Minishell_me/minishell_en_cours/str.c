#include "../include/minishell.h"

int     custom_strlen (const char *str)
{
    size_t  length = 0;

    while (*str != '\0')
    {
        length++;
        str++;
    }
    return length;
}

int custom_strcmp(const char *str1, const char *str2)
{
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
            return (str1[i] - str2[i]);
        i++;
    }

    return (str1[i] - str2[i]);
}

int custom_strncmp(const char *str1, const char *str2, size_t n)
{
    while (n > 0 && *str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
        n--;
    }
    if (n == 0)
        return (0);
    return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

char *custom_strchr(const char *str, int c) {
    while (*str != '\0')
    {
        if (*str == c)
            return (char*)str;
        str++;
    }

    return NULL;
}

char *custom_strtok(char *str, const char *delim)
{
    static char *next_token = NULL;

    if (str != NULL)
        next_token = str;
    else if (next_token == NULL)
        return (NULL);

    // On ignore les délimiteurs au début de la chaîne
    while (*next_token && custom_strchr(delim, *next_token))
        next_token++;

    if (*next_token == '\0')
    {
        next_token = NULL;
        return (NULL);
    }

    char *token = next_token;
    // Recherche du prochain délimiteur pour diviser la chaîne en jetant les délimiteurs
    while (*next_token && !custom_strchr(delim, *next_token))
        next_token++;
    if (*next_token != '\0')
    {
        *next_token = '\0';
        next_token++;
    }
    else
        next_token = NULL;
    return (token);
}

char *custom_strcpy(char *dest, const char *src)
{
    if (dest == NULL || src == NULL)
        return NULL;

    char *result = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Ajout du caractère de fin de chaîne
    return (result);
}

char *custom_strdup(const char *str)
{
    size_t len;
    char *duplicate;

    if (str == NULL)
        return NULL;
    len = custom_strlen(str);
    duplicate = (char *)malloc((len + 1) * sizeof(char));
    if (duplicate == NULL)
        return NULL;
    custom_strcpy(duplicate, str);
    return (duplicate);
}

void *custom_memcpy(void *dest, const void *src, size_t n)
{
    char *d;
    const char *s;

    d = (char *)dest;
    s = (const char *)src;
    for (size_t i = 0; i < n; ++i)
        d[i] = s[i];
    return (dest);
}

void *my_memset(void *ptr, int value, size_t num)
{
    unsigned char *p;

    p = ptr;
    while (num--)
        *p++ = (unsigned char)value;
    return (ptr);
}

void *my_calloc(size_t num_elements, size_t element_size)
{
    size_t total_size;
    void *ptr;

    // Calcul de la taille totale nécessaire en octets
    total_size = num_elements * element_size;
    // Allocation de mémoire avec malloc
    ptr = malloc(total_size);
    if (ptr != NULL)
        // Initialisation explicite de la mémoire allouée à zéro avec memset
        my_memset(ptr, 0, total_size);
    return (ptr);
}

void *custom_realloc(void *ptr, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    if (ptr != NULL) 
    {
        custom_memcpy(new_ptr, ptr, new_size);
        free(ptr);
    }
    return (new_ptr);
}
char *custom_strcat(char *dest, const char *src)
{
    int dest_len = custom_strlen(dest);
    int i;

    for (i = 0; src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
    return (dest);
}

char *custom_strrchr(const char *str, int character)
{
    char *result = NULL;

    while (*str != '\0')
    {
        if (*str == character)
            result = (char *)str;
        str++;
    }
    if (character == '\0')
        return (char*)str;
    return (result);
}
