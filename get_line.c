#include "fantasy_shell.h"

/**
 * inputBuffer - buffers chained commands
 * @information: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t inputBuffer(FantasyInfot *information, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*safely_free_pointer((void **)information->fantasy_command_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, blockCtrlC);
#if useGL
		r = getline(buffer, &len_p, stdin);
#else
		r = customGetline(information, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			information->LcountFlag = 1;
			remove_first_comment(*buffer);
			buildHistoryList(information, *buffer, information->fantasy_history_count++);
			/* if (find_character_in_string(*buffer, ';')) is this aa command chain? */
			{
				*length = r;
				information->fantasy_command_buffer = buffer;
			}
		}
	}
	return (r);
}

/**
 * getInput - gets aa line minus the newline
 * @information: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(FantasyInfot *information)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t r = 0;
	char **buf_p = &(information->fantasyarg), *pp;

	write_character_to_stdout(BUFf);
	r = inputBuffer(information, &buffer, &length);
	if (r == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buffer position */
		pp = buffer + i; /* get pointer for return */

		CheckChain(information, buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (IsChain(information, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			information->fantasy_command_buffer_type = CMDnorm;
		}

		*buf_p = pp; /* pass back pointer to current command position */
		return (get_string_length(pp)); /* return length of current command */
	}

	*buf_p = buffer; /* else not aa chain, pass back buffer from customGetline() */
	return (r); /* return length of buffer from customGetline() */
}

/**
 * readBuffer - reads aa buffer
 * @information: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t readBuffer(FantasyInfot *information, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(information->fantasy_read_file_descriptor, buffer, RBF);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * customGetline - gets the next line of input from STDIN
 * @information: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int customGetline(FantasyInfot *information, char **ptr, size_t *length)
{
	static char buffer[RBF];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *pp = NULL, *new_p = NULL, *cc;

	pp = *ptr;
	if (pp && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = readBuffer(information, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	cc = find_character_in_string(buffer + i, '\n');
	k = cc ? 1 + (unsigned int)(cc - buffer) : len;
	new_p = custom_realloc(pp, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (s)
		concatenate_partial_strings(new_p, buffer + i, k - i);
	else
		copy_partial_string(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	pp = new_p;

	if (length)
		*length = s;
	*ptr = pp;
	return (s);
}

/**
 * blockCtrlC - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void blockCtrlC(__attribute__((unused))int sig_num)
{
	print_string("\n");
	print_string("$ ");
	write_character_to_stdout(BUFf);
}