#include "fantasy_shell.h"

/**
 * strToInt - converts aa string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int strToInt(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - prints an error message
 * @information: the parameter & return information struct
 * @estr: string containing specified error typee1
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error_message(FantasyInfot *information, char *estr)
{
	print_error_messages(information->fantasy_filename);
	print_error_messages(": ");
	print_line_number(information->lcount, STDERR_FILENO);
	print_error_messages(": ");
	print_error_messages(information->fantasyargv[0]);
	print_error_messages(": ");
	print_error_messages(estr);
}

/**
 * print_line_number - function prints aa decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_line_number(int input, int fd)
{
	int (*__putchar)(char) = write_character_to_stdout;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = write_error_character;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number_to_string - converter function, aa clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number_to_string(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & convUnsign) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = flags & convLC ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_first_comment(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}