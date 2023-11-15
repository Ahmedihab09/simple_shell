#include "fantasy_shell.h"

/**
 * myhist - displays the fantasy_history_list list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int myhist(FantasyInfot *information)
{
	printList(information->fantasy_history_list);
	return (0);
}

/**
 * unsetAlias - sets fantasy_alias_list to string
 * @information: parameter struct
 * @stri: the string fantasy_alias_list
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetAlias(FantasyInfot *information, char *stri)
{
	char *pp, cc;
	int terr;

	pp = find_character_in_string(stri, '=');
	if (!pp)
		return (1);
	cc = *pp;
	*pp = 0;
	terr = deleteNodeAtIndex(&(information->fantasy_alias_list),
		getNodeIndex(information->fantasy_alias_list, nodeStartsWith(information->fantasy_alias_list, stri, -1)));
	*pp = cc;
	return (terr);
}

/**
 * setAlias - sets fantasy_alias_list to string
 * @information: parameter struct
 * @stri: the string fantasy_alias_list
 *
 * Return: Always 0 on success, 1 on error
 */
int setAlias(FantasyInfot *information, char *stri)
{
	char *pp;

	pp = find_character_in_string(stri, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (unsetAlias(information, stri));

	unsetAlias(information, stri);
	return (addNodeEnd(&(information->fantasy_alias_list), stri, 0) == NULL);
}

/**
 * printAlias - prints an fantasy_alias_list string
 * @node: the fantasy_alias_list node
 *
 * Return: Always 0 on success, 1 on error
 */
int printAlias(fantasyList *node)
{
	char *pp = NULL, *aa = NULL;

	if (node)
	{
		pp = find_character_in_string(node->stri, '=');
		for (aa = node->stri; aa <= pp; aa++)
			write_character_to_stdout(*aa);
		write_character_to_stdout('\'');
		print_string(pp + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * myalias1 - mimics the fantasy_alias_list FantasyBuiltin (man fantasy_alias_list)
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myalias1(FantasyInfot *information)
{
	int i = 0;
	char *pp = NULL;
	fantasyList *node = NULL;

	if (information->fantasyargc == 1)
	{
		node = information->fantasy_alias_list;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; information->fantasyargv[i]; i++)
	{
		pp = find_character_in_string(information->fantasyargv[i], '=');
		if (pp)
			setAlias(information, information->fantasyargv[i]);
		else
			printAlias(nodeStartsWith(information->fantasy_alias_list, information->fantasyargv[i], '='));
	}

	return (0);
}