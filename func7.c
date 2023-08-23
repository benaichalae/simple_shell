#include "shell.h"


ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t p = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		p = getline(buf, &len_p, stdin);
#else
		p = _getline(info, buf, &len_p);
#endif
		if (p > 0)
		{
			if ((*buf)[p - 1] == '\n')
			{
				(*buf)[p - 1] = '\0';
				p--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			/*build_history_list(info, *buf, info->histcount++);*/
			{
				*len = p;
				info->cmd_buf = buf;
			}
		}
	}
	return (p);
}

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t b = 0;

	if (*i)
		return (0);
	b = read(info->readfd, buf, READ_BUF_SIZE);
	if (b >= 0)
		*i = b;
	return (b);
}

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t x = 0, y = 0;
	char *p = NULL, *new = NULL, *c;

	p = *ptr;
	if (p && length)
		y = *length;
	if (i == len)
		i = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	new = _realloc(p, y, y ? y + j : j + 1);
	if (!new)
		return (p ? free(p), -1 : -1);

	if (y)
		_strncat(new, buf + i, j - i);
	else
		_strncpy(new, buf + i, j - i + 1);

	y += j - i;
	i = j;
	p = new;

	if (length)
		*length = y;
	*ptr = p;
	return (y);
}
