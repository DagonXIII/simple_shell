#include "main.h"
/**
 * main - runs the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *resolved_path = NULL, *copy = NULL, *buffer = NULL;
	char *PATH = NULL;
	char **av = NULL;
	int exit_status = 0;

	signal(SIGINT, SIG_IGN);
	PATH = get_env("PATH");
	if (PATH == NULL)
		return (-1);
	while (1)
	{
		av = NULL;
		display_prompt();
		buffer = read_user_input();
		if (*buffer != '\0')
		{
			av = tokenize(buffer);
			if (av == NULL)
			{
				free(buffer);
				continue;
			}
			resolved_path = executable_path(av, PATH, copy);
			if (handle_builtin(av, buffer, exit_status) != 0)
				continue;
			exit_status = fork_and_run(av, buffer, resolved_path);
		}
		else
			free(buffer);
	}
	return (0);
}

