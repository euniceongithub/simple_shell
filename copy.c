#include "shell.h"

/**
 * copyString - copies a string
 * @dest: the destination string
 * @src: the source string
 * @n: number of characters to be copied
 *
 * Return: the concatenated string.
 */
char *copyString(char *dest, char *src, int n)
{
	int i, j;
	char *s;

	s = dest;
	i = 0;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * concatString - concatenates two strings
 * @dest: the destination of the strings
 * @src: source of string
 * @n: number of bytes allowed
 *
 * @n: number of bytes allowed
 */
char *concatString(char *dest, char *src, int n)
{
	int i, j;
	char *s;

	s = dest;
	i = 0;
	j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * charLocator - find the address of a character in a string
 * @s: the string
 * @c: character
 *
 * Return: NULL if the character is not found, or character address
 */
char *charLocator(char *s, char c)
{
	for (; *s != '\0'; s++)
	{
		if (*s == c)
			return (s);
	}
	return (NULL);
}
