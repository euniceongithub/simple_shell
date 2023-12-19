#include "shell.h"

/**
 * chainBuffer - buffers chained commands
 * @content: parameter struct
 * @memBuffer: buffer address
 * @len: address of len variable
 *
 * Return: bytes read
 */
ssize_t chainBuffer(info_t *content, char **memBuffer, size_t *len)
{
	ssize_t x;
	size_t lenPtr;

	x = 0;
	lenPtr = 0;

	if (!*len)
	{
		free(*memBuffer);
		*memBuffer = NULL;
		signal(SIGINT, blockCtrlC);
		#if GET_LINE
		x = getline(memBuffer, &lenPtr, stdin);
		#else
		x = fetchInput(content, memBuffer, &lenPtr);
		#endif
		if (x > 0)
		{
			if ((*memBuffer)[x - 1] == '\n')
			{
				(*memBuffer)[x - 1] = '\0';
				x--;
			}
			content->linecount_prec_check = 1;
			elimComent(*memBuffer);
			addHistory(content, *memBuffer, content->n_history++);
			{
				*len = x;
				content->bufferCommand = memBuffer;
			}
		}
	}
	return (x);
}

/**
 * fetchContent - function to get the main content of a line
 * @content: parameter struct
 *
 * Return: bytes read.
 */
ssize_t fetchContent(info_t *content)
{
	static char *memBuffer;
	static size_t i, j, len;
	ssize_t x;
	char **buf_p = &(content->arg), *p;

	x = 0;

	_putchar(BUF_ERASE);
	x = chainBuffer(content, &memBuffer, &len);
	if (x == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = memBuffer + i;
		chainCheck(content, memBuffer, &j, i, len);
		while (j < len)
		{
			if (dm_test(content, memBuffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = j + 1;
			if (i >= len)
			{
				i = len = 0;
				content->bufferCommandType = NORM_COMMAND;
			}
		}

		*buf_p = p;
		return (stringLen(p));
	}
		*buf_p = memBuffer;
	return (x);
}

/**
 * bufferRead - reads buffer
 * @content: parameter struct
 * @memBuffer: buffer
 * @i: size
 *
 * Return: x.
 */
ssize_t bufferRead(info_t *content, char *memBuffer, size_t *i)
{
	ssize_t x;

	x = 0;

	if (*i)
		return (0);
	x = read(content->check_file_des, memBuffer, SIZEOF_BUFFER);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * fetchInput - gets the next line of input from STDIN
 * @content: parameter struct
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr buffer
 *
 * Return: s
 */
int fetchInput(info_t *content, char **ptr, size_t *length)
{
	static char memBuffer[SIZEOF_BUFFER];
	static size_t i, len;
	size_t k;
	ssize_t x = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	x = bufferRead(content, memBuffer, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = charLocator(memBuffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - memBuffer) : len;
	new_p = rrealloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		concatString(new_p, memBuffer + i, k - i);
	else
		copyString(new_p, memBuffer + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * blockCtrlC - blocks ctrl+C command
 * @sig_num: signal number
 *
 * Return: void.
 */
void blockCtrlC(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_ERASE);
}
