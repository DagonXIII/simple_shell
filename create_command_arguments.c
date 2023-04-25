#include "main.h"
/**
 * tokenize - creates array of tokens based on user string
 * @buffer: pointer to user string
 *
 * Return: pointer to array of user strings
 */
char **tokenize(char *buffer)
{
	char *token = NULL;
	int i = 0, word_count = 0;
	char *delimiter = " \n";
	char **av = NULL;

	word_count = split_string(buffer);
	if (!word_count)
		return (NULL);
	av = malloc((word_count + 1) * sizeof(char *));
	if (av == NULL)
		exit(1);
	token = strtok(buffer, delimiter);
	while (token != NULL)
	{
		av[i] = duplicate_string(token);
		token = strtok(NULL, delimiter);
		i++;
	}
	av[i] = NULL;
	return (av);
}
/**
 * split_path - counts the number of PATH members
 * @str: pointer to string to count
 *
 * Return: number of PATH members
 */
int split_path(char *str)
{
	int i, search_flag = 1, word_count = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ':' && search_flag == 1)
		{
			word_count += 1;
			search_flag = 0;
		}
		if (str[i + 1] == ':')
		{
			search_flag = 1;
		}
	}
	return (word_count);
}
/**
 * compare_path_strings - compares PATH with environ to find PATH value
 * @s1: pointer PATH string
 * @s2: pointer to environ string with actual value
 *
 * Return: 0 on success
 */
int compare_path_strings(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s2[i] != '='; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}
/**
 * concatenate_path - concats user string with PATH member string and /
 * @tmp: static array to store concatenated string
 * @av: pointer to array of user strings
 * @tok: pointer to PATH token
 *
 * Return: 0 on success
 */
char *concatenate_path(char *tmp, char **av, char *tok)
{
	int len = 0;

	set_memory(tmp, 0, 256);
	len = string_length(tok) + string_length(av[0]) + 2;
	concatenate_strings(tmp, tok);
	concatenate_strings(tmp, "/");
	concatenate_strings(tmp, av[0]);
	tmp[len - 1] = '\0';
	return (tmp);
}
