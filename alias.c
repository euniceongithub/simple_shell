#include "shell.h"

/**
 * sh_history - history across shell
 * @content: parameter struct
 *
 * Return: Always 0.
 */
int sh_history(info_t *content)
{
	listPrint(content->history);
	return (0);
}

/**
 * resetAlias - sets alias to string
 * @content: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error.
 */
int resetAlias(info_t *content, char *str)
{
	char *p, c;
	int ret;

	p = charLocator(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deleteNode(&(content->alias),
			receive_index(content->alias, beginPrefix(content->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * stringAlias - sets alias to string
 * @content: parameter struct
 * @str: the string alias
 *
 * Return: Always 0.
 */
int stringAlias(info_t *content, char *str)
{
	char *p;

	p = charLocator(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (resetAlias(content, str));
	resetAlias(content, str);
	return (tailToNode(&(content->alias), str, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0.
 */
int printAlias(list_t *node)
{
	char *p, *a;

	p = NULL;
	a = NULL;

	if (node)
	{
		p = charLocator(node->str, '=');
		while (a <= p)
		{
			_putchar(*a);
			a++;
		}
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");

		return (0);
	}
	return (1);
}

/**
 * ama_alias - amateur alias built-in
 * @content: struct for future arguments
 *
 * Return: Always 0.
 */
int ama_alias(info_t *content)
{
	int i;
	char *p;
	list_t *node;

	i = 0;
	p = NULL;
	node = NULL;

	if (content->argc == 1)
	{
		node = content->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; content->argv[i]; i++)
	{
		p = charLocator(content->argv[i], '=');
		if (p)
			stringAlias(content, content->argv[i]);
		else
			printAlias(beginPrefix(content->alias, content->argv[i], '='));
	}
	return (0);
}
