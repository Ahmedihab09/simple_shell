#include "fantasy_shell.h"

/**
 * initializeInfo - initializes FantasyInfot struct
 * @information: struct address
 */
void initializeInfo(FantasyInfot *information)
{
	information->fantasyarg = NULL;
	information->fantasyargv = NULL;
	information->fantasypath = NULL;
	information->fantasyargc = 0;
}

/**
 * populateInfo - initializes FantasyInfot struct
 * @information: struct address
 * @av: argument vector
 */
void populateInfo(FantasyInfot *information, char **av)
{
	int i = 0;

	information->fantasy_filename = av[0];
	if (information->fantasyarg)
	{
		information->fantasyargv = split_string_by_delimiters(information->fantasyarg, " \t");
		if (!information->fantasyargv)
		{

			information->fantasyargv = malloc(sizeof(char *) * 2);
			if (information->fantasyargv)
			{
				information->fantasyargv[0] = duplicate_string(information->fantasyarg);
				information->fantasyargv[1] = NULL;
			}
		}
		for (i = 0; information->fantasyargv && information->fantasyargv[i]; i++)
			;
		information->fantasyargc = i;

		ReplaceAliases(information);
		ReplaceVariables(information);
	}
}

/**
 * freeInfo - frees FantasyInfot struct fields
 * @information: struct address
 * @all: true if freeing all fields
 */
void freeInfo(FantasyInfot *information, int all)
{
	free_string_array(information->fantasyargv);
	information->fantasyargv = NULL;
	information->fantasypath = NULL;
	if (all)
	{
		if (!information->fantasy_command_buffer)
			free(information->fantasyarg);
		if (information->fantasy_environment_list)
			freeList(&(information->fantasy_environment_list));
		if (information->fantasy_history_list)
			freeList(&(information->fantasy_history_list));
		if (information->fantasy_alias_list)
			freeList(&(information->fantasy_alias_list));
		free_string_array(information->environ);
			information->environ = NULL;
		safely_free_pointer((void **)information->fantasy_command_buffer);
		if (information->fantasy_read_file_descriptor > 2)
			close(information->fantasy_read_file_descriptor);
		write_character_to_stdout(BUFf);
	}
}