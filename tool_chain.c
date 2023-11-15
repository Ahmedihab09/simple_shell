#include "fantasy_shell.h"

/**
 * IsChain - test if current char in buffer is aa chain delimeter
 * @information: the parameter struct
 * @buffer: the char buffer
 * @pp: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int IsChain(FantasyInfot *information, char *buffer, size_t *pp)
{
	size_t j = *pp;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		information->fantasy_command_buffer_type = CMDor;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		information->fantasy_command_buffer_type = CMDand;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		information->fantasy_command_buffer_type = CMDchain;
	}
	else
		return (0);
	*pp = j;
	return (1);
}

/**
 * CheckChain - checks we should continue chaining based on last fantasy_command_status
 * @information: the parameter struct
 * @buffer: the char buffer
 * @pp: address of current position in buffer
 * @i: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void CheckChain(FantasyInfot *information, char *buffer, size_t *pp, size_t i, size_t length)
{
	size_t j = *pp;

	if (information->fantasy_command_buffer_type == CMDand)
	{
		if (information->fantasy_command_status)
		{
			buffer[i] = 0;
			j = length;
		}
	}
	if (information->fantasy_command_buffer_type == CMDor)
	{
		if (!information->fantasy_command_status)
		{
			buffer[i] = 0;
			j = length;
		}
	}

	*pp = j;
}

/**
 * ReplaceAliases - replaces an aliases in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceAliases(FantasyInfot *information)
{
	int i;
	fantasyList *node;
	char *pp;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(information->fantasy_alias_list, information->fantasyargv[0], '=');
		if (!node)
			return (0);
		free(information->fantasyargv[0]);
		pp = find_character_in_string(node->stri, '=');
		if (!pp)
			return (0);
		pp = duplicate_string(pp + 1);
		if (!pp)
			return (0);
		information->fantasyargv[0] = pp;
	}
	return (1);
}

/**
 * ReplaceVariables - replaces vars in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceVariables(FantasyInfot *information)
{
	int i = 0;
	fantasyList *node;

	for (i = 0; information->fantasyargv[i]; i++)
	{
		if (information->fantasyargv[i][0] != '$' || !information->fantasyargv[i][1])
			continue;

		if (!compare_strings(information->fantasyargv[i], "$?"))
		{
			ReplaceString(&(information->fantasyargv[i]),
				duplicate_string(convert_number_to_string(information->fantasy_command_status, 10, 0)));
			continue;
		}
		if (!compare_strings(information->fantasyargv[i], "$$"))
		{
			ReplaceString(&(information->fantasyargv[i]),
				duplicate_string(convert_number_to_string(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(information->fantasy_environment_list, &information->fantasyargv[i][1], '=');
		if (node)
		{
			ReplaceString(&(information->fantasyargv[i]),
				duplicate_string(find_character_in_string(node->stri, '=') + 1));
			continue;
		}
		ReplaceString(&information->fantasyargv[i], duplicate_string(""));

	}
	return (0);
}

/**
 * ReplaceString - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}