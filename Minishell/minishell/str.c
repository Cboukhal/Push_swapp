/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboukhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:46:48 by cboukhal          #+#    #+#             */
/*   Updated: 2024/02/06 14:51:47 by cboukhal         ###   ########.fr       */
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
	size_t		length;
	const char	*temp;
	char		*original_dest;
	char		*dest;

	length = 0;
	temp = src;
	while (*temp++ != '\0')
		length++;
	dest = (char *) malloc((length + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	original_dest = dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (original_dest);
}

char	*my_strrchr(const char *str, int c)
{
	const char	*last_occurrence;

	last_occurrence = NULL;
	while (*str != '\0')
	{
		if (*str == c)
			last_occurrence = str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return ((char *)last_occurrence);
}
