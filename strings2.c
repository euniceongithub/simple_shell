#include "shell.h"

/**
 * splitString - splits a string into words
 * @str: input string
 * @d: dm string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitString(char *str, char *d)
{
	int w, x, y, z, char_acters;
	char **s;

	char_acters = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (w = 0; str[w] != '\0'; w++)
		if (!dm_check(str[w], d) && (dm_check(str[w + 1], d) || !str[w + 1]))
			char_acters++;
	if (char_acters == 0)
		return (NULL);
	s = malloc((1 + char_acters) * sizeof(char *));
	if (!s)
		return (NULL);
	for (w = 0, x = 0; x < char_acters; x++)
	{
		while (dm_check(str[w], d))
			w++;
		y = 0;
		while (!dm_check(str[w + y], d) && str[w + y])
			y++;
		s[x] = malloc((y + 1) * sizeof(char));
		if (!s[x])
		{
			for (y = 0; y < x; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[x][z] = str[w++];
		s[x][z] = 0;
	}
	s[x] = NULL;
	return (s);
}

/**
 * split_String - splits a string into words
 * @str: input string
 * @d: dm
 * Return: a pointer to an array of strings on success, NULL on failure
 */
char **split_String(char *str, char d)
{
	int w, x, y, z, char_acters = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (w = 0; str[w] != '\0'; w++)
		if ((str[w] != d && str[w + 1] == d) ||
		    (str[w] != d && !str[w + 1]) || str[w + 1] == d)
			char_acters++;
	if (char_acters == 0)
		return (NULL);
	s = malloc((1 + char_acters) * sizeof(char *));
	if (!s)
		return (NULL);
	for (w = 0, x = 0; x < char_acters; x++)
	{
		while (str[w] == d && str[w] != d)
			w++;
		y = 0;
		while (str[w + y] != d && str[w + y] && str[w + y] != d)
			y++;
		s[x] = malloc((y + 1) * sizeof(char));
		if (!s[x])
		{
			for (y = 0; y < x; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[x][z] = str[w++];
		s[x][z] = 0;
	}
	s[x] = NULL;
	return (s);
}
