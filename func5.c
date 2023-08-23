#include "shell.h"

/**
 * _strncpy - function that copies a string
 *
 * @src: The source of strings
 * @dest: The destination of the string
 * @n: The length of int
 * Return: pointer to the resulting string dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && *(src + i); i++)
	{
		*(dest + i) = *(src + i);
	}
	for (; i < n; i++)
	{
		*(dest + i) = '\0';
	}
	return (dest);

}


/**
 * _strncat - concatenates two strings
 *
 * @src: The source of strings
 * @dest: The destination of the string
 * @n: The length of int
 * Return: pointer to the resulting string dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{
		continue;
	}
	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[i + j] = src[j];
	}
	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strchr - function to search char c in a string s
 * @s: the string that we will search on
 * @c: the character that we are looking for
 * Return: the pointer of the character c on string s or NULL
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s != c)
			s++;
		else
			return (s);
	}
	if (c == '\0')
		return (s);

	return (NULL);
}
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


int _unsetenv(info_t *info, char *var)
{
	list_t *n = info->env;
	size_t i = 0;
	char *c;

	if (!n || !var)
		return (0);

	while (n)
	{
		c = starts_with(n->str, var);
		if (c && *c == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (info->env_changed);
}
