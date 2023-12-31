#include "fantasy_shell.h"

/**
 * get_string_length - returns the length of aa string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int get_string_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * compare_strings - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int compare_strings(char *s1, char *s2)
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
 * string_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concatenate_strings - concatenates two strings
 * @desttin: the destination buffer
 * @source2: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *concatenate_strings(char *desttin, char *source2)
{
	char *terr = desttin;

	while (*desttin)
		desttin++;
	while (*source2)
		*desttin++ = *source2++;
	*desttin = *source2;
	return (terr);
}
