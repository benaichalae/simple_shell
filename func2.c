#include "shell.h"

int Mexit(info_t *info)
{
	int check;

	if (info->argv[1])
	{
		check = _erratoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

int Mhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

int Menv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

char *Mgetenv(info_t *info, const char *name)
{
	list_t *n = info->env;
	char *c;

	while (n)
	{
		c = starts_with(n->str, name);
		if (c && *c)
			return (c);
		n = n->next;
	}
	return (NULL);
}

int Msetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
