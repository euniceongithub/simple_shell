#include "shell.h"

/**
 * custom_puts - custom function to print a string
 * @str: string to be printed
 *
 * Return: NULL.
 */
void custom_puts(char *str)
{
	int i;

	i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		custom_putchar(str[i]);
		i++;
	}
}

/**
 * custom_putchar - custom function to print characters
 * @c: The character to print
 *
 * Return:  1 on success and -1 on failure.
 */
int custom_putchar(char c)
{
	static int i;
	static char memBuffer[WRITE_BUF_SIZE];

	if (c == BUF_ERASE || i >= WRITE_BUF_SIZE)
	{
		write(2, memBuffer, i);
		i = 0;
	}
	if (c != BUF_ERASE)
		memBuffer[i++] = c;
	return (1);
}

/**
 * print_to_fd - writes character to given file descriptor
 * @c: character to be printed
 * @file_des: File Descriptor
 *
 * Return:  1 on success and -1 on failure.
 */
int print_to_fd(char c, int file_des)
{
	static int i;
	static char memBuffer[WRITE_BUF_SIZE];

	if (c == BUF_ERASE || i >= WRITE_BUF_SIZE)
	{
		write(file_des, memBuffer, i);
		i = 0;
	}
	if (c != BUF_ERASE)
		memBuffer[i++] = c;
	return (1);
}

/**
 * printInputStr - prints input string
 * @str: string to be printed
 * @file_des: File Descriptor
 *
 * Return: number of characters printed.
 */
int printInputStr(char *str, int file_des)
{
	int n;

	n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += print_to_fd(*str++, file_des);
	}
	return (n);
}
