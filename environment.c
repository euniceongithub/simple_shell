#include "shell.h"

/**
 * print_curr_environ - prints the current environment
 * @content: Struct address
 *
 * Return: Always 0.
 */
int print_curr_environ(info_t *content)
{
	print_list_str(content->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @content: Structure address
 * @name: env var name
 *
 * Return: NULL.
 */
char *get_env(info_t *content, const char *name)
{
	list_t *node = content->env;
	char *p;

	while (node)
	{
		p = checkHay(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * init_env - Initialize the environment variable
 * @content: Struct address
 *
 * Return: Always 0.
 */
int init_env(info_t *content)
{
	if (content->argc != 3)
	{
		custom_puts("Warning! Arguments are too many or too few.\n");
		return (1);
	}
	if (set_env(content, content->argv[1], content->argv[2]))
		return (0);
	return (1);
}

/**
 * rem_env - Remove an environment variable
 * @content: Struct address
 *
 * Return: Always 0.
 */
int rem_env(info_t *content)
{
	int i;

	if (content->argc == 1)
	{
		custom_puts("Warning! Arguments are too few.\n");
		return (1);
	}
	for (i = 1; i <= content->argc; i++)
		removeEnv(content, content->argv[i]);
	return (0);
}

/**
 * content_env - fills in the linked list with its contents
 * @content: Struct address
 *
 * Return: Always 0.
 */
int content_env(info_t *content)
{
	list_t *node;
	size_t i;

	node = NULL;

	for (i = 0; environ[i]; i++)
		tailToNode(&node, environ[i], 0);
	content->env = node;
	return (0);
}
