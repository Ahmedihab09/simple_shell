#include "fantasy_shell.h"

/**
 * exitShell - exits the shell
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with aa given exit fantasy_command_status
 *         (0) if information.fantasyargv[0] != "exit"
 */
int exitShell(FantasyInfot *information)
{
	int _extchk;

	if (information->fantasyargv[1])  /* If there is an exit arguement */
	{
		_extchk = strToInt(information->fantasyargv[1]);
		if (_extchk == -1)
		{
			information->fantasy_command_status = 2;
			print_error_message(information, "Illegal number: ");
			print_error_messages(information->fantasyargv[1]);
			write_error_character('\n');
			return (1);
		}
		information->err_number = strToInt(information->fantasyargv[1]);
		return (-2);
	}
	information->err_number = -1;
	return (-2);
}

/**
 * changeDirectory - changes the current directory of the process
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int changeDirectory(FantasyInfot *information)
{
	char *s, *directory, buffer[1024];
	int chdir_return;

	s = getcwd(buffer, 1024);
	if (!s)
		print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!information->fantasyargv[1])
	{
		directory = getEnvironmentVariable(information, "HOME=");
		if (!directory)
			chdir_return = /* TODO: what should this be? */
				chdir((directory = getEnvironmentVariable(information, "PWD=")) ? directory : "/");
		else
			chdir_return = chdir(directory);
	}
	else if (compare_strings(information->fantasyargv[1], "-") == 0)
	{
		if (!getEnvironmentVariable(information, "OLDPWD="))
		{
			print_string(s);
			write_character_to_stdout('\n');
			return (1);
		}
		print_string(getEnvironmentVariable(information, "OLDPWD=")), write_character_to_stdout('\n');
		chdir_return = /* TODO: what should this be? */
			chdir((directory = getEnvironmentVariable(information, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_return = chdir(information->fantasyargv[1]);
	if (chdir_return == -1)
	{
		print_error_message(information, "can't cd to ");
		print_error_messages(information->fantasyargv[1]), write_error_character('\n');
	}
	else
	{
		my_setenv(information, "OLDPWD", getEnvironmentVariable(information, "PWD="));
		my_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * showHelp - changes the current directory of the process
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int showHelp(FantasyInfot *information)
{
	char **argArray;

	argArray = information->fantasyargv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
		print_string(*argArray); /* temp att_unused workaround */
	return (0);
}