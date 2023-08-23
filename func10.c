#include "shell.h"

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

int is_cmd(info_t *info, char *path)
{
	struct stat file_stat;

	(void)info;
	if (!path || stat(path, &file_stat))
		return (0);
	if (file_stat.st_mode & S_IFREG)
		return (1);
	return (0);
}

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = start, k = 0;

	while (i < stop)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
		i++;
	}
	buf[k] = 0;
	return (buf);
}

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, position = 0;
	char *path;

	if (pathstr == NULL)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, position, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (pathstr[i] == '\0')
				break;
			position = i;
		}
		i++;
	}
	return (NULL);
}
