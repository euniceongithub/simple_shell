#include "shell.h"

/**
 * copyToDest - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *copyToDest(char *dest, char *src)
{
	int i;

	i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * stringDup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *stringDup(const char *str)
{
	int length;
	char *ret;

	length = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i;

	i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char memBuffer[WRITE_BUF_SIZE];

	if (c == BUF_ERASE || i >= WRITE_BUF_SIZE)
	{
		write(1, memBuffer, i);
		i = 0;
	}
	if (c != BUF_ERASE)
		memBuffer[i++] = c;
	return (1);
}
