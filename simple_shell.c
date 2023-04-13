#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main()
{
	char command[BUFFER_SIZE];
	char *args[2];
	args[1] = NULL;

	while (1)
	{
		printf("#cisfun$ ");
		fgets(command, BUFFER_SIZE, stdin);

		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		command[strcspn(command, "\n")] = '\0';

		if (access(command, X_OK) == -1)
		{
			printf("%s: command not found\n", command);
		}

		else
		{
			args[0] = command;
			if (fork() == 0)
			{
				execve(args[0], args, NULL);
			}

			else
			{
				wait(NULL);
			}
		}
	}

	return 0;
}
