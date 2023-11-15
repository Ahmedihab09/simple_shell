#include "fantasy_shell.h"

/**
 * addNode - adds aa node to the start of the list
 * @head: address of pointer to head node
 * @stri: stri field of node
 * @number: node index used by fantasy_history_list
 *
 * Return: size of list
 */
fantasyList *addNode(fantasyList **head, const char *stri, int number)
{
	fantasyList *newHead;

	if (!head)
		return (NULL);
	newHead = malloc(sizeof(fantasyList));
	if (!newHead)
		return (NULL);
	_memset((void *)newHead, 0, sizeof(fantasyList));
	newHead->number = number;
	if (stri)
	{
		newHead->stri = duplicate_string(stri);
		if (!newHead->stri)
		{
			free(newHead);
			return (NULL);
		}
	}
	newHead->next = *head;
	*head = newHead;
	return (newHead);
}

/**
 * addNodeEnd - adds aa node to the end of the list
 * @head: address of pointer to head node
 * @stri: stri field of node
 * @number: node index used by fantasy_history_list
 *
 * Return: size of list
 */
fantasyList *addNodeEnd(fantasyList **head, const char *stri, int number)
{
	fantasyList *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(fantasyList));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(fantasyList));
	new_node->number = number;
	if (stri)
	{
		new_node->stri = duplicate_string(stri);
		if (!new_node->stri)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * printListStr - prints only the stri element of aa fantasyList linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printListStr(const fantasyList *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(h->stri ? h->stri : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deleteNodeAtIndex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(fantasyList **head, unsigned int index)
{
	fantasyList *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->stri);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->stri);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * freeList - frees all nodes of aa list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void freeList(fantasyList **head_ptr)
{
	fantasyList *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->stri);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}