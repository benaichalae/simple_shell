#include "shell.h"

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

char **splitter(char *str, char *d)
{
	int i = 0, j, k, m, n = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";

	while (str[i] != '\0')
	{
		if (!delimeter(str[i], d) && (delimeter(str[i + 1], d) || !str[i + 1]))
		{
			n++;
		}
		i++;
	}
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (s == NULL)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (delimeter(str[i], d))
			i++;
		k = 0;
		while (!delimeter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

int replace_alias(info_t *info)
{
	int i = 0;
	list_t *n;
	char *c;
	
	while (i < 10)
	{
		n = node_starts_with(info->alias, info->argv[0], '=');

		if (!n)
			return 0;

		free(info->argv[0]);
		c = _strchr(n->str, '=');

		if (!c)
			return 0;

		c = _strdup(c + 1);

		if (!c)
			return 0;

		info->argv[0] = c;
		 i++;
	}
	return (1);
}

int replace_vars(info_t *info)
{
	int i = 0;
	list_t *n;
	char *env_key = NULL;

	while (info->argv[i])
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			i++;
			continue;
		}

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), _strdup(convert(info->status, 10, 0)));
		}
		else if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]), _strdup(convert(getpid(), 10, 0)));
		}
		else
		{
			env_key = &(info->argv[i][1]);
			n = node_starts_with(info->env, env_key, '=');

			if (n)
			{
				replace_string(&(info->argv[i]), _strdup(_strchr(n->str, '=') + 1));
			}
			else
			{
				replace_string(&(info->argv[i]), _strdup(""));
			}
		}
		i++;
	}
	return (0);
}
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
