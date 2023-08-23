#include "shell.h"

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


int delimeter(char c, char *delim)/*is_delim*/
{
	for (; *delim; delim++)
	{
		if (*delim == c)
			return (1);
	}
	return (0);
}

/*int alphabet(int c)/*_isalpha*/
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}*/

int _atoi(char *s)
{
	int i = 0;
	unsigned int result = 0;
	int sign = 1;
	int flag = 0;

	while (s[i])
	{
		if (s[i] == 45)
		{
			sign *= -1;
		}

		while (s[i] >= 48 && s[i] <= 57)
		{
			flag = 1;
			result = (result * 10) + (s[i] - '0');
			i++;
		}
		if (flag == 1)
		{
			break;
		}
		i++;
	}
	result *= sign;
	return (result);
}

int Mhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
