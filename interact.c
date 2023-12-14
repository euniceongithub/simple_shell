#include "shell.h"

/**
 * check_interact - checks if the shell is in interactive mode
 * @content: struct address
 *
 * Return: 1 for True Value, 0 for False value
 */
int check_interact(info_t *content)
{
		return (isatty(STDIN_FILENO) && content->check_file_des <= 2);
}

/**
 * dm_check - function to determine if character is a delimiter
 * @c: checked char
 * @dm: checked delimiter
 *
 * Return: 0 for False value and 1 for True value
 */
int dm_check(char c, char *dm)
{
	while (*dm != '\0')
	{
		if (*dm == c)
		{
			return (1);
		}
		dm++;
	}
	return (0);
}

/**
 * check_letter - function to determine if character is a letter
 * @c: checked character
 *
 * Return: 0 on failure, 1 on success.
 */
int check_letter(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * converter - function to convert from string to integer
 * @s: string to be converted
 *
 * Return: product of result and magnitude
 */
int converter(char *s)
{
	int result;
	int mag;

	result = 0;
	mag = 1;

	if (*s == '-')
	{
		mag = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result * mag);
}
