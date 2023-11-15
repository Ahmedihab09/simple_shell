#include "fantasy_shell.h"

/**
 * copy_string - copies aa string
 * @desttin: the destination
 * @source2: the source
 *
 * Return: pointer to destination
 */
char *copy_string(char *desttin, char *source2)
{
	int i = 0;

	if (desttin == source2 || source2 == 0)
		return (desttin);
	while (source2[i])
	{
		desttin[i] = source2[i];
		i++;
	}
	desttin[i] = 0;
	return (desttin);
}

/**
 * duplicate_string - duplicates aa string
 * @stri: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplicate_string(const char *stri)
{
	int length = 0;
	char *terr;

	if (stri == NULL)
		return (NULL);
	while (*stri++)
		length++;
	terr = malloc(sizeof(char) * (length + 1));
	if (!terr)
		return (NULL);
	for (length++; length--;)
		terr[length] = *--stri;
	return (terr);
}

/**
 *print_string - prints an input string
 *@stri: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *stri)
{
	int i = 0;

	if (!stri)
		return;
	while (stri[i] != '\0')
	{
		write_character_to_stdout(stri[i]);
		i++;
	}
}

/**
 * write_character_to_stdout - writes the character cc to stdout
 * @cc: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character_to_stdout(char cc)
{
	static int i;
	static char buffer[WBF];

	if (cc == BUFf || i >= WBF)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (cc != BUFf)
		buffer[i++] = cc;
	return (1);
}
