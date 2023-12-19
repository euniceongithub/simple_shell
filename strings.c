#include "shell.h"

/**
 * stringLen - returns the length of a string
 * @s: string
 *
 * Return: length of string
 */
int stringLen(char *s)
{
	int length;

	length = 0;

	if (!s)
		return (0);

	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * stringCmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: positive if s1 > s2, negative if s1 < s2, zero if s1 == s2.
 */
int stringCmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * checkHay - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *checkHay(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concatToDest - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *concatToDest(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
