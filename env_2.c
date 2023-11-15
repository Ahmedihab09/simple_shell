#include "fantasy_shell.h"

/**
 * copyEnvironment - returns the string array copy of our environ
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **copyEnvironment(FantasyInfot *information)
{
	if (!information->environ || information->fantasy_environment_changed)
	{
		information->environ = listToStrings(information->fantasy_environment_list);
		information->fantasy_environment_changed = 0;
	}

	return (information->environ);
}

/**
 * my_unsetenv - Remove an environment variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string fantasy_environment_list var property
 */
int my_unsetenv(FantasyInfot *information, char *var)
{
	fantasyList *node = information->fantasy_environment_list;
	size_t i = 0;
	char *pp;

	if (!node || !var)
		return (0);

	while (node)
	{
		pp = string_starts_with(node->stri, var);
		if (pp && *pp == '=')
		{
			information->fantasy_environment_changed = deleteNodeAtIndex(&(information->fantasy_environment_list), i);
			i = 0;
			node = information->fantasy_environment_list;
			continue;
		}
		node = node->next;
		i++;
	}
	return (information->fantasy_environment_changed);
}

/**
 * my_setenv - Initialize aa new environment variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string fantasy_environment_list var property
 * @value: the string fantasy_environment_list var value
 *  Return: Always 0
 */
int my_setenv(FantasyInfot *information, char *var, char *value)
{
	char *buffer = NULL;
	fantasyList *node;
	char *pp;

	if (!var || !value)
		return (0);

	buffer = malloc(get_string_length(var) + get_string_length(value) + 2);
	if (!buffer)
		return (1);
	copy_string(buffer, var);
	concatenate_strings(buffer, "=");
	concatenate_strings(buffer, value);
	node = information->fantasy_environment_list;
	while (node)
	{
		pp = string_starts_with(node->stri, var);
		if (pp && *pp == '=')
		{
			free(node->stri);
			node->stri = buffer;
			information->fantasy_environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(information->fantasy_environment_list), buffer, 0);
	free(buffer);
	information->fantasy_environment_changed = 1;
	return (0);
}