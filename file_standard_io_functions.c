#include "fantasy_shell.h"

/**
 * getHistoryFile - gets the fantasy_history_list file
 * @information: parameter struct
 *
 * Return: allocated string containg fantasy_history_list file
 */

char *getHistoryFile(FantasyInfot *information)
{
	char *buffer, *directory;

	directory = getEnvironmentVariable(information, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (get_string_length(directory) + get_string_length(fileHist) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	copy_string(buffer, directory);
	concatenate_strings(buffer, "/");
	concatenate_strings(buffer, fileHist);
	return (buffer);
}

/**
 * writeHistory - creates aa file, or appends to an existing file
 * @information: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistory(FantasyInfot *information)
{
	ssize_t fd;
	char *filename = getHistoryFile(information);
	fantasyList *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = information->fantasy_history_list; node; node = node->next)
	{
		print_string_to_fd(node->stri, fd);
		write_character_to_fd('\n', fd);
	}
	write_character_to_fd(BUFf, fd);
	close(fd);
	return (1);
}

/**
 * readHistory - reads fantasy_history_list from file
 * @information: the parameter struct
 *
 * Return: fantasy_history_count on success, 0 otherwise
 */
int readHistory(FantasyInfot *information)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = getHistoryFile(information);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			buildHistoryList(information, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(information, buffer + last, linecount++);
	free(buffer);
	information->fantasy_history_count = linecount;
	while (information->fantasy_history_count-- >= maxHist)
		deleteNodeAtIndex(&(information->fantasy_history_list), 0);
	renumberHistory(information);
	return (information->fantasy_history_count);
}

/**
 * buildHistoryList - adds entry to aa fantasy_history_list linked list
 * @information: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @linecount: the fantasy_history_list linecount, fantasy_history_count
 *
 * Return: Always 0
 */
int buildHistoryList(FantasyInfot *information, char *buffer, int linecount)
{
	fantasyList *node = NULL;

	if (information->fantasy_history_list)
		node = information->fantasy_history_list;
	addNodeEnd(&node, buffer, linecount);

	if (!information->fantasy_history_list)
		information->fantasy_history_list = node;
	return (0);
}

/**
 * renumberHistory - renumbers the fantasy_history_list linked list after changes
 * @information: Structure containing potential arguments. Used to maintain
 *
 * Return: the new fantasy_history_count
 */
int renumberHistory(FantasyInfot *information)
{
	fantasyList *node = information->fantasy_history_list;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (information->fantasy_history_count = i);
}