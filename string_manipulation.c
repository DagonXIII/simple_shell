#include "main.h"
/**
 * duplicate_string - duplicates a string
 * @str: pointer to string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *duplicate_string(char *str)
{
	int i;
	char *dest_str = NULL;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		;
	dest_str = malloc(sizeof(char) * (i + 1));
	if (dest_str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		dest_str[i] = str[i];
	}
	dest_str[i] = '\0';
	return (dest_str);
}
/**
 * split_string - counts number of words in string
 * @str: pointer to string to count
 *
 * Return: number of words in string
 */
int split_string(char *str)
{
	int i, search_flag = 1, word_count = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && search_flag == 1)
		{
			word_count += 1;
			search_flag = 0;
		}
		if (str[i + 1] == ' ')
			search_flag = 1;
	}
	return (word_count);
}
/**
 * compare_strings - compares two strings
 * @s1: char type
 * @s2: char type
 *
 * Return: integer value
 */
int compare_strings(const char *s1, const char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}
/**
 * concatenate_strings - concatenates two strings
 * @dest: char type
 * @src: char type
 * i - integer type
 * j - integer type
 * Return: char type
 */
char *concatenate_strings(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++, i++)
		dest[i] = src[j];
	dest[i] = '\0';
	return (dest);
}
/**
 * string_length - returns the length of a string
 * @s: character type
 * i - integer type
 * Return: integer type
 */
int string_length(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		;
	return (i);
}
