#include "shell.h"

/**
 * execCheck - determines if a file is an executable command
 * @content: the content struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int execCheck(info_t *content, char *path)
{
	struct stat s_t;

	(void)content;
	if (!path || stat(path, &s_t))
		return (0);
	if (s_t.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupChar - duplicates characters
 * @pathstr: path string
 * @start: start index
 * @stop: stop index
 *
 * Return: pointer to new buffer.
 */
char *dupChar(char *pathstr, int start, int stop)
{
	static char memBuffer[1024];
	int i, k;

	i = 0;
	k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			memBuffer[k++] = pathstr[i];
	memBuffer[k] = 0;
	return (memBuffer);
}

/**
 * findCommand - finds this cmd in the path string
 * @content: the content struct
 * @pathstr: the path string
 * @cmd: the command to find
 *
 * Return: path of command on success, NULL on failure.
 */
char *findCommand(info_t *content, char *pathstr, char *cmd)
{
	int i, presentAddress;
	char *path;

	i = 0;
	presentAddress = 0;

	if (!pathstr)
		return (NULL);
	if ((stringLen(cmd) > 2) && checkHay(cmd, "./"))
	{
		if (execCheck(content, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupChar(pathstr, presentAddress, i);
			if (!*path)
				concatToDest(path, cmd);
			else
			{
				concatToDest(path, "/");
				concatToDest(path, cmd);
			}
			if (execCheck(content, path))
				return (path);
			if (!pathstr[i])
				break;
			presentAddress = i;
		}
		i++;
	}
	return (NULL);
}
