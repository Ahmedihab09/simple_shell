#include "fantasy_shell.h"

/**
 * main - entry point
 * @ac: fantasyarg count
 * @av: fantasyarg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	FantasyInfot information[] = { FANTASY_INFO_INIT };
	int fd = 2;

	/*printNumbersFrom1To10;
	return (0);*/

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_error_messages(av[0]);
				print_error_messages(": 0: Can't open ");
				print_error_messages(av[1]);
				write_error_character('\n');
				write_error_character(BUFf);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->fantasy_read_file_descriptor = fd;
	}
	populateEnvironmentList(information);
	readHistory(information);
	hsh(information, av);
	return (EXIT_SUCCESS);
}