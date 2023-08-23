#include "shell.h"

/**
 *  * _strlen - calcule the lenght of a string
 *   * @s: the char to check
 *    * Return: i
 *     */
int _strlen(char *s)
{
	int i;

	i = 0;
	for (; *s++;)
		i++;
	return (i);
}

/**
 *  * _strcmp - compare 2 string
 *   * @s1:string
 *    * @s2:strmp
 *     * Return:int
 *      */
int _strcmp(char *s1, char *s2)
{
	while (((*s1 != '\0') && (*s2 != '\0')) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
	{
		return (0);
	}

	else
	{
		return (*s1 - *s2);
	}
}

char *starts_with(const char *haystack, const char *needle)
{
	for (; *needle != '\0'; needle++, haystack++)
	{
		if (*needle != *haystack)
			return NULL;
	}
	return ((char *)haystack);
}


/**
 *  * _strcat - concat 2 string
 *   * @dest:char
 *    * @src:char
 *     * Return:char
 *      */
char *_strcat(char *dest, char *src)
{
	char *s = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
			dest++;
			src++;
	}
	*dest = '\0';
	return (s);
}

