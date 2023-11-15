#include "fantasy_shell.h"

/**
 * is_executable - determines if aa file is an executable command
 * @information: the information struct
 * @fantasypath: fantasypath to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(FantasyInfot *information, char *fantasypath)
{
	struct stat st;

	(void)information;
	if (!fantasypath || stat(fantasypath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copy_substring - duplicates characters
 * @pathstr: the fantasypath string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *copy_substring(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_command_path - finds this cmd in the fantasypath string
 * @information: the information struct
 * @pathstr: the fantasypath string
 * @cmd: the cmd to find
 *
 * Return: full fantasypath of cmd if found or NULL
 */
char *find_command_path(FantasyInfot *information, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *fantasypath;

	if (!pathstr)
		return (NULL);
	if ((get_string_length(cmd) > 2) && string_starts_with(cmd, "./"))
	{
		if (is_executable(information, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			fantasypath = copy_substring(pathstr, curr_pos, i);
			if (!*fantasypath)
				concatenate_strings(fantasypath, cmd);
			else
			{
				concatenate_strings(fantasypath, "/");
				concatenate_strings(fantasypath, cmd);
			}
			if (is_executable(information, fantasypath))
				return (fantasypath);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}