#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @content: Struct address
 *
 * Return: String array of environment variables.
 */
char **get_environ(info_t *content)
{
	if (environ != content->environ || content->env_changed)
	{
		ffree(&content->environ);
		content->environ = listToStrings(content->env);
		content->env_changed = 0;
	}
	return (environ);
}

/**
 * removeEnv - Remove env variable
 * @content: Struct address
 * @var: env var property
 *
 * Return: 1 on sucess, 0 on failure
 */
int removeEnv(info_t *content, char *var)
{
	list_t *node = content->env;
	size_t i;
	char *ptr;

	i = 0;

	if (!node || !var)
		return (0);
	while (node)
	{
		ptr = checkHay(node->str, var);
		if (ptr && *ptr == '=')
		{
			content->env_changed = deleteNode(&(content->env), i);
			i = 0;
			node = content->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (content->env_changed);
}

/**
 * set_env - set env variable
 * @content: Struct address
 * @var: env var string
 * @value: env var value
 *
 * Return: Always 0.
 */
int set_env(info_t *content, char *var, char *value)
{
	char *memBuffer;
	list_t *node;
	char *ptr;

	memBuffer = NULL;
	if (!var || !value)
		return (0);
	memBuffer = malloc(stringLen(var) + stringLen(value) + 2);
	if (!memBuffer)
		return (1);
	copyToDest(memBuffer, var);
	concatToDest(memBuffer, "=");
	concatToDest(memBuffer, value);
	node = content->env;
	while (node)
	{
		ptr = checkHay(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = memBuffer;
			content->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	tailToNode(&(content->env), memBuffer, 0);
	free(memBuffer);
	content->env_changed = 1;
	return (0);
}
