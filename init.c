#include "shell.h"

/**
 * initInfo - initializes info_t
 * @content: struct address
 *
 * Return: NULL.
 */
void initInfo(info_t *content)
{
	content->arg = NULL;
	content->argv = NULL;
	content->path = NULL;
	content->argc = 0;
}

/**
 * argInfo - attaches an argument to info_t
 * @content: struct address
 * @av: argument vector
 */
void argInfo(info_t *content, char **av)
{
	int i;

	i = 0;

	content->fname = av[0];
	if (content->arg)
	{
		content->argv = splitString(content->arg, " \t");
		if (!content->argv)
		{
			content->argv = malloc(sizeof(char *) * 2);
			if (content->argv)
			{
				content->argv[0] = stringDup(content->arg);
				content->argv[1] = NULL;
			}
		}
		for (i = 0; content->argv && content->argv[i]; i++)
			;
		content->argc = i;
		replaceAlias(content);
		replaceVar(content);
	}
}

/**
 * infoFree - frees info_t struct fields
 * @content: struct address
 * @all: true value
 *
 * Return: null.\
 */
void infoFree(info_t *content, int all)
{
	ffree(content->argv);
	content->argv = NULL;
	content->path = NULL;
	if (all)
	{
		if (!content->bufferCommand)
			free(content->arg);
		if (content->env)
			freeNodes(&(content->env));
		if (content->history)
			freeNodes(&(content->history));
		if (content->alias)
			freeNodes(&(content->alias));
		ffree(content->environ);
		content->environ = NULL;
		bfree((void **)content->bufferCommand);
		if (content->check_file_des > 2)
			close(content->check_file_des);
		_putchar(BUF_ERASE);
	}
}
