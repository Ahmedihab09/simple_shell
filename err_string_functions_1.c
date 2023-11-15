#include "fantasy_shell.h"

/**
 *print_error_messages - prints an input string
 * @stri: the string to be printed
 *
 * Return: Nothing
 */
void print_error_messages(char *stri)
{
	int i = 0;

	if (!stri)
		return;
	while (stri[i] != '\0')
	{
		write_error_character(stri[i]);
		i++;
	}
}

/**
 * write_error_character - writes the character cc to stderr
 * @cc: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_error_character(char cc)
{
	static int i;
	static char buffer[WBF];

	if (cc == BUFf || i >= WBF)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (cc != BUFf)
		buffer[i++] = cc;
	return (1);
}

/**
 * write_character_to_fd - writes the character cc to given fd
 * @cc: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character_to_fd(char cc, int fd)
{
	static int i;
	static char buffer[WBF];

	if (cc == BUFf || i >= WBF)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (cc != BUFf)
		buffer[i++] = cc;
	return (1);
}

/**
 *print_string_to_fd - prints an input string
 * @stri: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int print_string_to_fd(char *stri, int fd)
{
	int i = 0;

	if (!stri)
		return (0);
	while (*stri)
	{
		i += write_character_to_fd(*stri++, fd);
	}
	return (i);
}