#include "shell.h"

/**
 *  * _strcpy - copy the string pointed to by src to dest
 *   * @dest: char to check
 *    * @src: char to check
 *     * Return: 0 is success
 *      */
char *_strcpy(char *dest, char *src)
{
	int a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';
	return (dest);
}

/**
 *  * _strdup - returns a pointer to a newly allocated space in memory
 *   * @str: the source string
 *    * Return: returns a pointer to the duplicated string.
 *     * It returns NULL if insufficient memory was available
 *      */
char *_strdup(const char *str)
{
	char *c;
	int i, j = 0;

	if (str == NULL)
		return (NULL);
	while (str[j] != '\0')
		j++;
	c = (char *)malloc((sizeof(char) * j) + 1);
	if (c == NULL)
		return (NULL);
	for (i = 0; i < j; i++)
		c[i] = str[i];
	c[j] = '\0';
	return (c);
}

/**
 *  * _puts - prints a string
 *   * @str: the string
 *    *
 *     * Return: the length of the string
 *      */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 *  * _putchar - writes the character c to stdout
 *   * @c: The character to print
 *    *
 *     * Return: On success 1.
 *      * On error, -1 is returned, and errno is set appropriately.
 *       */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

