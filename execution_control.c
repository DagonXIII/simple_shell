#include "main.h"
/**
 * display_prompt - writes a prompt
 *
 * Return: 0 on sucess
 */
int display_prompt(void)
{
	char *prompt = "#cisfun$ ";
	ssize_t write_count = 0;

	if (isatty(STDIN_FILENO) == 1)
	{
		write_count = write(STDOUT_FILENO, prompt, 8);
		if (write_count == -1)
			exit(0);
	}
	return (0);
}
/**
 * read_user_input - reads stdin and stores it in a buffer
 *
 * Return: a pointer to the buffer
 */
char *read_user_input(void)
{
	ssize_t read_count = 0;
	size_t n = 0;
	char *buffer = NULL;
	int i = 0;

	read_count = getline(&buffer, &n, stdin);
	if (read_count == -1)
	{
		free(buffer);
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (buffer[read_count - 1] == '\n' || buffer[read_count - 1] == '\t')
		buffer[read_count - 1] = '\0';
	for (i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '#' && buffer[i - 1] == ' ')
		{
			buffer[i] = '\0';
			break;
		}
	}
	return (buffer);
}
/**
 * executable_path - finds the string to call execve on
 * @av: pointer to array of user strings
 * @PATH: pointer to PATH string
 * @copy: pointer to copy of PATH string
 *
 * Return: a pointer to string to call execve on
 */
char *executable_path(char **av, char *PATH, char *copy)
{
	char *tok = NULL, *executable_path = NULL, *concatstr = NULL;
	static char tmp[256];
	int PATHcount = 0, fullpathflag = 0, z = 0, toklen = 0;
	struct stat h;

	copy = NULL;
	copy = duplicate_string(PATH);
	PATHcount = split_path(copy);
	tok = strtok(copy, ": =");
	while (tok != NULL)
	{
		concatstr = concatenate_path(tmp, av, tok);
		if (stat(concatstr, &h) == 0)
		{
			executable_path = concatstr;
			fullpathflag = 1;
			break;
		}
		if (z < PATHcount - 2)
		{
			toklen = string_length(tok);
			if (tok[toklen + 1] == ':')
			{
				if (stat(av[0], &h) == 0)
				{
					executable_path = av[0];
					fullpathflag = 1;
					break;
				}
			}
		}
		z++;
		tok = strtok(NULL, ":");
	}
	if (fullpathflag == 0)
		executable_path = av[0];
	free(copy);
	return (executable_path);
}
/**
 * handle_builtin - check if first user string is a built-in
 * @av: pointer to array of user of strings
 * @buffer: pointer to user string
 * @exit_status: exit status of execve
 * Return: 1 if user string is equal to env or 0 otherwise
 */
int handle_builtin(char **av, char *buffer, int exit_status)
{
	int i;

	if (compare_strings(av[0], "env") == 0)
	{
		print_env();
	}
	else if (compare_strings(av[0], "exit") == 0)
	{
	exit(exit_status);
	}
	else if (compare_strings(av[0], "cd") == 0)
	{
		char *dir = NULL;
		if (av[1] == NULL || compare_strings(av[1], "~") == 0)
		{
			dir = getenv("HOME");
		}
		else if (compare_strings(av[1], "-") == 0)
		{
			dir = getenv("OLDPWD");
			printf("%s\n", dir);
		}
		else
		{
			dir = av[1];
		}
		if (dir == NULL)
		{
			printf("cd: HOME not set\n");
		}
		else if (chdir(dir) == -1)
		{
            printf("cd: %s: No such file or directory\n", dir);
		}
		else
		{
			char cwd[1024];
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				setenv("OLDPWD", getenv("PWD"), 1);
				setenv("PWD", cwd, 1);
			}
			else
			{
				printf("cd: Error getting current working directory\n");
			}
		}
	}
	else if (compare_strings(av[0], "setenv") == 0)
	{
		if (av[1] == NULL || av[2] == NULL || av[3] != NULL)
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return 1;
		}
		if (setenv(av[1], av[2], 1) == -1)
		{
			fprintf(stderr, "setenv: failed to set %s=%s\n", av[1], av[2]);
			return 1;
		}
	}
	else if (compare_strings(av[0], "unsetenv") == 0)
	{
		if (av[1] == NULL || av[2] != NULL)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return 1;
		}
		if (unsetenv(av[1]) == -1)
		{
			fprintf(stderr, "unsetenv: failed to unset %s\n", av[1]);
			return 1;
		}
	}
	else
	{
		return 0;
	}

	for (i = 0; av[i]; i++)
		free(av[i]);
	free(av);
	free(buffer);
	return 1;
}
/**
 * fork_and_run - create child process to execute based on user input
 * @av: pointer to array of user of strings
 * @buffer: pointer to user string
 * @resolved_path: pointer to user input
 *
 * Return: 0 on success
 */
int fork_and_run(char **av, char *buffer, char *resolved_path)
{
	int i, status, result, exit_status = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pid == 0)
	{
		result =  execve(resolved_path, av, environ);
		if (result == -1)
		{
			perror(av[0]);
			for (i = 0; av[i]; i++)
				free(av[i]);
			free(av);
			free(buffer);
			exit(127);
		}
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	for (i = 0; av[i]; i++)
		free(av[i]);
	free(av);
	free(buffer);
	return (exit_status);
}

