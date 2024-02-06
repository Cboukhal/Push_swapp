/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboukhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:46:48 by cboukhal          #+#    #+#             */
/*   Updated: 2024/02/06 13:56:53 by cboukhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	my_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (*str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

int	my_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

char	*my_strcpy(char *dest, const char *src)
{
	char	*original_dest;

	original_dest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

char	*my_strdup(const char *src)
{
	size_t  	length;
	const char	*temp;

	length = 0;
	temp = src;
	while (*temp++ != '\0')
		length++;
	char *dest = (char*)malloc((length + 1) * sizeof(char));
	if (dest == NULL)
		return NULL;
	char *original_dest = dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return original_dest;
}

char* my_strrchr(const char *str, int c)
{
    const char *last_occurrence;

    last_occurrence = NULL;
    while (*str != '\0')
    {
        if (*str == c)
            last_occurrence = str;
        str++;
    }
    if (c == '\0')
        return (char*)str;
    return (char*)last_occurrence;
}

char* my_strcat(char *dest, const char *src)
{
    char *original_dest;

    original_dest = dest; 
    while (*dest != '\0')
        dest++;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}

char* my_strncpy(char *dest, const char *src, size_t n)
{
    char *original_dest;

    original_dest = dest;
    while (n > 0 && *src != '\0')
    {
        *dest++ = *src++;
        n--;
    }
    while (n > 0)
    {
        *dest++ = '\0';
        n--;
    }
    return original_dest;
}

int my_strncmp(const char *str1, const char *str2, size_t n)
{
    while (n > 0)
    {
        if (*str1 == '\0' || *str2 == '\0')
            return *str1 - *str2;
        if (*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
        n--;
    }
    return 0;
}

size_t my_strspn(const char *str, const char *chars) {
    size_t count;
    const char *c;

    count = 0;
    while (*str != '\0')
    {
        c = chars;
        while (*c != '\0')
        {
            if (*str == *c)
            {
                ++count;
                break;
            }
	++c;
	}
	if (*c == '\0')
		return count;
	++str;
	}
	return count;
}

char *my_strtok(char *str, const char *delim)
{
	static char *last_token = NULL;
	char *token_end;

	if (str == NULL)
	str = last_token;
	if (str == NULL || *str == '\0')
		return NULL;
	str += strspn(str, delim);
	if (*str == '\0')
		return NULL;
	token_end = str + strcspn(str, delim);
	if (*token_end == '\0')
		last_token = NULL;
	else
	{
		*token_end = '\0';
		last_token = token_end + 1;
	}
	return (str);
}
