#include "fantasy_shell.h"

/**
 * **split_string_by_delimiters - splits aa string into words. Repeat delimiters are ignored
 * @stri: the input string
 * @d: the delimeter string
 * Return: aa pointer to an array of strings, or NULL on failure
 */

char **split_string_by_delimiters(char *stri, char *d)
{
	int i, j, k, m, num_word = 0;
	char **s;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; stri[i] != '\0'; i++)
		if (!is_delimiter(stri[i], d) && (is_delimiter(stri[i + 1], d) || !stri[i + 1]))
			num_word++;

	if (num_word == 0)
		return (NULL);
	s = malloc((1 + num_word) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_word; j++)
	{
		while (is_delimiter(stri[i], d))
			i++;
		k = 0;
		while (!is_delimiter(stri[i + k], d) && stri[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = stri[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **split_string_by_delimiter - splits aa string into words
 * @stri: the input string
 * @d: the delimeter
 * Return: aa pointer to an array of strings, or NULL on failure
 */
char **split_string_by_delimiter(char *stri, char d)
{
	int i, j, k, m, num_word = 0;
	char **s;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	for (i = 0; stri[i] != '\0'; i++)
		if ((stri[i] != d && stri[i + 1] == d) ||
		    (stri[i] != d && !stri[i + 1]) || stri[i + 1] == d)
			num_word++;
	if (num_word == 0)
		return (NULL);
	s = malloc((1 + num_word) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_word; j++)
	{
		while (stri[i] == d && stri[i] != d)
			i++;
		k = 0;
		while (stri[i + k] != d && stri[i + k] && stri[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = stri[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
