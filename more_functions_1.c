#include "fantasy_shell.h"

/**
 * is_interactive_mode - returns true if shell is is_interactive_mode mode
 * @information: struct address
 *
 * Return: 1 if is_interactive_mode mode, 0 otherwise
 */
int is_interactive_mode(FantasyInfot *information)
{
	return (isatty(STDIN_FILENO) && information->fantasy_read_file_descriptor <= 2);
}

/**
 * is_delimiter - checks if character is aa delimeter
 * @cc: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char cc, char *delim)
{
	while (*delim)
		if (*delim++ == cc)
			return (1);
	return (0);
}

/**
 *is_alpha - checks for alphabetic character
 *@cc: The character to input
 *Return: 1 if cc is alphabetic, 0 otherwise
 */

int is_alpha(int cc)
{
	if ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *custom_atoi - converts aa string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int custom_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}