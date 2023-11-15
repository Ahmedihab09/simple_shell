#include "fantasy_shell.h"

/**
 * env - prints the current environment
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env(FantasyInfot *information)
{
	printListStr(information->fantasy_environment_list);
	return (0);
}

/**
 * env - gets the value of an environ variable
 * @information: Structure containing potential arguments. Used to maintain
 * @name: fantasy_environment_list var name
 *
 * Return: the value
 */
char *getEnvironmentVariable(FantasyInfot *information, const char *name)
{
	fantasyList *node = information->fantasy_environment_list;
	char *pp;

	while (node)
	{
		pp = string_starts_with(node->stri, name);
		if (pp && *pp)
			return (pp);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvironmentVariable - Initialize aa new environment variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int setEnvironmentVariable(FantasyInfot *information)
{
	if (information->fantasyargc != 3)
	{
		print_error_messages("Incorrect number of arguements\n");
		return (1);
	}
	if (my_setenv(information, information->fantasyargv[1], information->fantasyargv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unsetEnvironmentVariable(FantasyInfot *information)
{
	int i;

	if (information->fantasyargc == 1)
	{
		print_error_messages("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= information->fantasyargc; i++)
		my_unsetenv(information, information->fantasyargv[i]);

	return (0);
}

/**
 * populateEnvironmentList - populates fantasy_environment_list linked list
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(FantasyInfot *information)
{
	fantasyList *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	information->fantasy_environment_list = node;
	return (0);
}