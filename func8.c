#include "shell.h"

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *next;

	if (!head)
		return (NULL);
	next = malloc(sizeof(list_t));
	if (!next)
		return (NULL);
	_memset((void *)next, 0, sizeof(list_t));
	next->num = num;
	if (str)
	{
		next->str = _strdup(str);
		if (!next->str)
		{
			free(next);
			return (NULL);
		}
	}
	next->next = *head;
	*head = next;
	return (next);
}

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *next, *n;

	if (!head)
		return (NULL);

	n = *head;
	next = malloc(sizeof(list_t));
	if (!next)
		return (NULL);
	_memset((void *)next, 0, sizeof(list_t));
	next->num = num;
	if (str)
	{
		next->str = _strdup(str);
		if (!next->str)
		{
			free(next);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = next;
	}
	else
		*head = next;
	return (next);
}


size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *n, *prev;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		n = *head;
		*head = (*head)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *head;
	while (n)
	{
		if (i == index)
		{
			prev->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		i++;
		prev = n;
		n = n->next;
	}
	return (0);
}

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
