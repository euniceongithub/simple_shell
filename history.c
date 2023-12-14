#include "shell.h"

/**
 * fetchHistory - fetches the history file
 * @content: parameter struct
 *
 * Return: allocated string containg history file
 */
char *fetchHistory(info_t *content)
{
	char *memBuffer, *dir;

	dir = get_env(content, "HOME=");
	if (!dir)
		return (NULL);
	memBuffer = malloc(sizeof(char) * (stringLen(dir) + stringLen(HISTORY_FILE) + 2));
	if (!memBuffer)
		return (NULL);
	memBuffer[0] = 0;
	copyToDest(memBuffer, dir);
	concatToDest(memBuffer, "/");
	concatToDest(memBuffer, HISTORY_FILE);
	return (memBuffer);
}

/**
 * printHistory - creates a file, or appends to an existing file
 * @content: the parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int printHistory(info_t *content)
{
	ssize_t file_des;
	char *fileTitle = fetchHistory(content);
	list_t *node = NULL;

	if (!fileTitle)
		return (-1);
	file_des = open(fileTitle, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fileTitle);
	if (file_des == -1)
		return (-1);
	for (node = content->history; node; node = node->next)
	{
		printInputStr(node->str, file_des);
		print_to_fd('\n', file_des);
	}print_to_fd(BUF_ERASE, file_des);
	close(file_des);
	return (1);
}

/**
 * getHistory - reads history from file
 * @content: parameter struct
 *
 * Return: n_history on success, 0 on failure
 */
int getHistory(info_t *content)
{
	int i, finalContent = 0, n_lines = 0;
	ssize_t file_des, rdLen, f_size = 0;
	struct stat s_t;
	char *memBuffer = NULL, *fileTitle = fetchHistory(content);

	if (!fileTitle)
		return (0);
	file_des = open(fileTitle, O_RDONLY);
	free(fileTitle);
	if (file_des == -1)
		return (0);
	if (!fstat(file_des, &s_t))
		f_size = s_t.st_size;
	if (f_size < 2)
		return (0);
	memBuffer = malloc(sizeof(char) * (f_size + 1));
	if (!memBuffer)
		return (0);
	rdLen = read(file_des, memBuffer, f_size);
	memBuffer[f_size] = 0;
	if (rdLen <= 0)
		return (free(memBuffer), 0);
	close(file_des);
	for (i = 0; i < f_size; i++)
		if (memBuffer[i] == '\n')
		{
			memBuffer[i] = 0;
			addHistory(content, memBuffer + finalContent, n_lines++);
			finalContent = i + 1;
		}
	if (finalContent != i)
		addHistory(content, memBuffer + finalContent, n_lines++);
	free(memBuffer);
	content->n_history = n_lines;
	while (content->n_history-- >= HISTORY_MAX)
		deleteNode(&(content->history), 0);
	hstry_orgnsd(content);
	return (content->n_history);
}

/**
 * addHistory - adds entry to a history linked list
 * @content: Struct address
 * @memBuffer: buffer
 * @n_lines: n_lines and n_history
 *
 * Return: Always 0.
 */
int addHistory(info_t *content, char *memBuffer, int n_lines)
{
	list_t *node;

	node = NULL;

	if (content->history)
		node = content->history;
	tailToNode(&node, memBuffer, n_lines);
	if (!content->history)
		content->history = node;
	return (0);
}

/**
 * hstry_orgnsd - reorganises the history linked list after changes
 * @content: Struct address
 *
 * Return: i.
 */
int hstry_orgnsd(info_t *content)
{
    int i;
    list_t *node;

    i = 0;

    for (node = content->history; node != NULL; node = node->next)
    {
        node->num = i++;
    }

    content->n_history = i;
    return (i);
}
