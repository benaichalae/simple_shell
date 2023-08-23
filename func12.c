#include "shell.h"


int hsh(info_t *info, char **av)
{
	ssize_t x = 0;
	int builtin = 0;

	while (x != -1 && builtin != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(info);
		if (x != -1)
		{
			set_info(info, av);
			builtin = find_builtin(info);
			if (builtin == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin);
}

int find_builtin(info_t *info)
{
	int i = 0, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", Mexit},
		{"env", Menv},
		{"help", Mhelp},
		{"history", Mhistory},
		{"setenv", Msetenv},
		{"unsetenv", Munsetenv},
		{NULL, NULL}
	};

	while (builtintbl[i].type)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
		i++;
	}
	return (built_in_ret);
}

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i = 0, k = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	while (info->arg[i])
	{
		if (!delimeter(info->arg[i], " \t\n"))
		{
			k++;
		}
		i++;
	}
	if (!k)
		return;


	path = find_path(info, Mgetenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || Mgetenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

void fork_cmd(info_t *info)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

