#include "../include/minishell.h"

char	*my_strncpy(char *dest, const char *src, size_t n)
{
	char	*original_dest;

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
	return (original_dest);
}

int	my_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 == '\0' || *str2 == '\0')
			return (*str1 - *str2);
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
		n--;
	}
	return (0);
}

char	*my_strcat(char *dest, const char *src)
{
	char	*original_dest;

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
	return (original_dest);
}

size_t	my_strspn(const char *str, const char *chars)
{
	size_t		count;
	const char	*c;

	count = 0;
	while (*str != '\0')
	{
		c = chars;
		while (*c != '\0')
		{
			if (*str == *c)
			{
				++count;
				break ;
			}
		++c;
		}
		if (*c == '\0')
			return (count);
		++str;
	}
	return (count);
}


size_t my_strcspn(const char *str, const char *reject)
{
    size_t count = 0;
    const char *s = str;
    const char *r;

    while (*s != '\0')
	{
        r = reject;
        while (*r != '\0')
		{
            if (*s == *r)
                return count;
            ++r;
        }
        ++count;
        ++s;
    }
    return count;
}

char	*my_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token_end;

	if (str == NULL)
	str = last_token;
	if (str == NULL || *str == '\0')
		return (NULL);
	str += strspn(str, delim);
	if (*str == '\0')
		return (NULL);
	token_end = str + my_strcspn(str, delim);
	if (*token_end == '\0')
		last_token = NULL;
	else
	{
		*token_end = '\0';
		last_token = token_end + 1;
	}
	return (str);
}
