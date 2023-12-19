#include "shell.h"

/**
 * dm_test - test if current char in buffer is a chain delimeter
 * @content: parameter struct
 * @memBuffer: character buffer
 * @p: address of current position in memBuffer
 *
 * Return: 1 on success, 0 on failure.
 */
int dm_test(info_t *content, char *memBuffer, size_t *p)
{
	size_t j;

	j = *p;

	if (memBuffer[j] == '|' && memBuffer[j + 1] == '|')
	{
		memBuffer[j] = 0;
		j++;
		content->bufferCommandType = OR_COMMAND;
	}
	else if (memBuffer[j] == '&' && memBuffer[j + 1] == '&')
	{
		memBuffer[j] = 0;
		j++;
		content->bufferCommandType = AND_COMMAND;
	}
	else if (memBuffer[j] == ';')
	{
		memBuffer[j] = 0;
		content->bufferCommandType = CHAIN_COMMAND;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chainCheck - checks we should continue chaining based on last status
 * @content: the parameter struct
 * @memBuffer: the char buffer
 * @p: address of current position in memBuffer
 * @i: starting position in memBuffer
 * @len: length of memBuffer
 *
 * Return: void.
 */
void chainCheck(info_t *content, char *memBuffer, size_t *p, size_t i, size_t len)
{
	size_t j;

	j = *p;

	if (content->bufferCommandType == AND_COMMAND)
	{
		if (content->status)
		{
			memBuffer[i] = 0;
			j = len;
		}
	}
	if (content->bufferCommandType == OR_COMMAND)
	{
		if (!content->status)
		{
			memBuffer[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replaceAlias - replaces an aliases in the tokenized string
 * @content: parameter struct
 *
 * Return: 1 on success, 0 on failure.
 */
int replaceAlias(info_t *content)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = beginPrefix(content->alias, content->argv[0], '=');
		if (!node)
			return (0);
		free(content->argv[0]);
		p = charLocator(node->str, '=');
		if (!p)
			return (0);
		p = stringDup(p + 1);
		if (!p)
			return (0);
		content->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVar - replaces vars in the tokenized string
 * @content: parameter struct
 *
 * Return: 1 on success, 0 on failure.
 */
int replaceVar(info_t *content)
{
	int i;
	list_t *node;

	i = 0;

	for (i = 0; content->argv[i]; i++)
	{
		if (content->argv[i][0] != '$' || !content->argv[i][1])
			continue;
		if (!stringCmp(content->argv[i], "$?"))
		{
			replace_string(&(content->argv[i]),
				stringDup(func_conversion(content->status, 10, 0)));
			continue;
		}
		if (!stringCmp(content->argv[i], "$$"))
		{
			replace_string(&(content->argv[i]),
				stringDup(func_conversion(getpid(), 10, 0)));
			continue;
		}
		node = beginPrefix(content->env, &content->argv[i][1], '=');
		if (node)
		{
			replace_string(&(content->argv[i]),
				stringDup(charLocator(node->str, '=') + 1));
			continue;
		}
		replace_string(&content->argv[i], stringDup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
