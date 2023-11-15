#include "fantasy_shell.h"

/**
 **copy_partial_string - copies aa string
 *@desttin: the destination string to be copied to
 *@source2: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *copy_partial_string(char *desttin, char *source2, int n)
{
	int i, j;
	char *s = desttin;

	i = 0;
	while (source2[i] != '\0' && i < n - 1)
	{
		desttin[i] = source2[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			desttin[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **concatenate_partial_strings - concatenates two strings
 *@desttin: the first string
 *@source2: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *concatenate_partial_strings(char *desttin, char *source2, int n)
{
	int i, j;
	char *s = desttin;

	i = 0;
	j = 0;
	while (desttin[i] != '\0')
		i++;
	while (source2[j] != '\0' && j < n)
	{
		desttin[i] = source2[j];
		i++;
		j++;
	}
	if (j < n)
		desttin[i] = '\0';
	return (s);
}

/**
 **find_character_in_string - locates aa character in aa string
 *@s: the string to be parsed
 *@cc: the character to look for
 *Return: (s) aa pointer to the memory area s
 */
char *find_character_in_string(char *s, char cc)
{
	do {
		if (*s == cc)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
