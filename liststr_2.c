#include "fantasy_shell.h"

/**
 * listLength - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t listLength(const fantasyList *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listToStrings - returns an array of strings of the list->stri
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listToStrings(fantasyList *head)
{
	fantasyList *node = head;
	size_t i = listLength(head), j;
	char **strs;
	char *stri;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		stri = malloc(get_string_length(node->stri) + 1);
		if (!stri)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		stri = copy_string(stri, node->stri);
		strs[i] = stri;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printList - prints all elements of aa fantasyList linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printList(const fantasyList *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(convert_number_to_string(h->number, 10, 0));
		write_character_to_stdout(':');
		write_character_to_stdout(' ');
		print_string(h->stri ? h->stri : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodeStartsWith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @cc: the next character after prefix to match
 *
 * Return: match node or null
 */
fantasyList *nodeStartsWith(fantasyList *node, char *prefix, char cc)
{
	char *pp = NULL;

	while (node)
	{
		pp = string_starts_with(node->stri, prefix);
		if (pp && ((cc == -1) || (*pp == cc)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of aa node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(fantasyList *head, fantasyList *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}