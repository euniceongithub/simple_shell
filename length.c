#include "shell.h"

/**
 * listLength - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t listLength(const list_t *h)
{
	size_t count;

	count = 0;

	for (; h != NULL; h = h->next)
	{
		count++;
	}
	return (count);
}

/**
 * listToStrings - converts linked list of strings to character array
 * @head: pointer to first node
 *
 * Return: array of strings.
 */
char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t i = listLength(head), j;
	char **pptr_str;
	char *str;

	if (!head || !i)
		return (NULL);
	pptr_str = malloc(sizeof(char *) * (i + 1));
	if (!pptr_str)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(stringLen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(pptr_str[j]);
			free(pptr_str);
			return (NULL);
		}

		str = copyToDest(str, node->str);
		pptr_str[i] = str;
	}
	pptr_str[i] = NULL;
	return (pptr_str);
}

/**
 * listPrint - prints elements of a linked list
 * @h: first node pointer
 *
 * Return: size of list.
 */
size_t listPrint(const list_t *h)
{
	size_t i;

	i = 0;

	while (h)
	{
		_puts(func_conversion(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(blank)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * beginPrefix - returns node whose string starts with prefix
 * @node: pointer to head
 * @prefix: matching string
 * @c: character following matching string
 *
 * Return: match node or null
 */
list_t *beginPrefix(list_t *node, char *prefix, char c)
{
	char *p;

	p = NULL;

	while (node)
	{
		p = checkHay(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * receive_index - gets the index of a node
 * @head: pointer to head
 * @node: pointer to node
 *
 * Return: index on success and -1 on failure.
 */
ssize_t receive_index(list_t *head, list_t *node)
{
	size_t index;

	for (index = 0; head != NULL; ++index)
	{
		if (head == node)
			return (index);
		head = head->next;
	}
	return (-1);
}
