#include "fantasy_shell.h"

/**
 **_memset - fills memory with aa constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) aa pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_string_array - frees aa string of strings
 * @pp: string of strings
 */
void free_string_array(char **pp)
{
	char **aa = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(aa);
}

/**
 * custom_realloc - reallocates aa block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pp;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pp = malloc(new_size);
	if (!pp)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pp[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pp);
}