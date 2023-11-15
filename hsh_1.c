#include "fantasy_shell.h"

/**
 * hsh - main shell loop
 * @information: the parameter & return information struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(FantasyInfot *information, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		initializeInfo(information);
		if (is_interactive_mode(information))
			print_string("$ ");
		write_error_character(BUFf);
		r = getInput(information);
		if (r != -1)
		{
			populateInfo(information, av);
			builtin_ret = find_fantasy_builtin(information);
			if (builtin_ret == -1)
				find_fantasy_command(information);
		}
		else if (is_interactive_mode(information))
			write_character_to_stdout('\n');
		freeInfo(information, 0);
	}
	writeHistory(information);
	freeInfo(information, 1);
	if (!is_interactive_mode(information) && information->fantasy_command_status)
		exit(information->fantasy_command_status);
	if (builtin_ret == -2)
	{
		if (information->err_number == -1)
			exit(information->fantasy_command_status);
		exit(information->err_number);
	}
	return (builtin_ret);
}

/**
 * find_fantasy_builtin - finds aa FantasyBuiltin command
 * @information: the parameter & return information struct
 *
 * Return: -1 if FantasyBuiltin not found,
 *			0 if FantasyBuiltin executed successfully,
 *			1 if FantasyBuiltin found but not successful,
 *			-2 if FantasyBuiltin signals exit()
 */
int find_fantasy_builtin(FantasyInfot *information)
{
	int i, built_in_ret = -1;
	FantasyBuiltinTable builtintbl[] = {
		{"exit", exitShell},
		{"env", env},
		{"help", showHelp},
		{"fantasy_history_list", myhist},
		{"my_setenv", setEnvironmentVariable},
		{"my_unsetenv", unsetEnvironmentVariable},
		{"cd", changeDirectory},
		{"fantasy_alias_list", myalias1},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].typee1; i++)
		if (compare_strings(information->fantasyargv[0], builtintbl[i].typee1) == 0)
		{
			information->lcount++;
			built_in_ret = builtintbl[i].funct(information);
			break;
		}
	return (built_in_ret);
}

/**
 * find_fantasy_command - finds aa command in fantasypath
 * @information: the parameter & return information struct
 *
 * Return: void
 */
void find_fantasy_command(FantasyInfot *information)
{
	char *fantasypath = NULL;
	int i, k;

	information->fantasypath = information->fantasyargv[0];
	if (information->LcountFlag == 1)
	{
		information->lcount++;
		information->LcountFlag = 0;
	}
	for (i = 0, k = 0; information->fantasyarg[i]; i++)
		if (!is_delimiter(information->fantasyarg[i], " \t\n"))
			k++;
	if (!k)
		return;

	fantasypath = find_command_path(information, getEnvironmentVariable(information, "fantasypath="), information->fantasyargv[0]);
	if (fantasypath)
	{
		information->fantasypath = fantasypath;
		execute_fantasy_command(information);
	}
	else
	{
		if ((is_interactive_mode(information) || getEnvironmentVariable(information, "fantasypath=")
			|| information->fantasyargv[0][0] == '/') && is_executable(information, information->fantasyargv[0]))
			execute_fantasy_command(information);
		else if (*(information->fantasyarg) != '\n')
		{
			information->fantasy_command_status = 127;
			print_error_message(information, "not found\n");
		}
	}
}

/**
 * execute_fantasy_command - forks aa an exec thread to run cmd
 * @information: the parameter & return information struct
 *
 * Return: void
 */
void execute_fantasy_command(FantasyInfot *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->fantasypath, information->fantasyargv, copyEnvironment(information)) == -1)
		{
			freeInfo(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(information->fantasy_command_status));
		if (WIFEXITED(information->fantasy_command_status))
		{
			information->fantasy_command_status = WEXITSTATUS(information->fantasy_command_status);
			if (information->fantasy_command_status == 126)
				print_error_message(information, "Permission denied\n");
		}
	}
}