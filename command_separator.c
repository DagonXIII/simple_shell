#include "main.h"

/**
 * read_input - reads input from the user
 *
 * Return: pointer to the input string
 */
char *read_input(void)
{
    char *input = NULL;
    size_t size = 0;

    if (getline(&input, &size, stdin) == EOF)
    {
        free(input);
        input = NULL;
    }

    return input;
}

/**
 * split_commands - splits the input string into separate commands
 * @input: pointer to the input string
 *
 * Return: pointer to an array of pointers to the individual commands
 */
char **split_commands(char *input)
{
    char **commands = NULL;
    char *command = NULL;
    size_t i = 0;

    if (input == NULL)
        return NULL;

    commands = malloc(sizeof(char *) * 10);
    if (commands == NULL)
        return NULL;

    command = strtok(input, ";");
    while (command != NULL)
    {
        commands[i++] = command;
        command = strtok(NULL, ";");
    }
    commands[i] = NULL;

    return commands;
}

/**
 * execute_single_command - executes a single command
 * @command: pointer to the command string
 *
 * Return: 0 on success, -1 on failure
 */
int execute_single_command(char *command)
{
    char **arguments = NULL;
    char *token = NULL;
    int i = 0, status;

    arguments = malloc(sizeof(char *) * 10);
    if (arguments == NULL)
        return -1;

    token = strtok(command, " ");
    while (token != NULL)
    {
        arguments[i++] = token;
        token = strtok(NULL, " ");
    }
    arguments[i] = NULL;

    status = execve(arguments[0], arguments, environ);
    if (status == -1)
    {
        perror("Error");
        free(arguments);
        return -1;
    }

    free(arguments);
    return 0;
}

/**
 * execute_commands - executes all the commands in the input array
 * @commands: pointer to an array of pointers to the individual commands
 *
 * Return: 0 on success, -1 on failure
 */
int execute_commands(char **commands)
{
    int i = 0;

    if (commands == NULL)
        return -1;

    while (commands[i] != NULL)
    {
        if (execute_single_command(commands[i++]) == -1)
            return -1;
    }

    return 0;
}

/**
 * free_memory - frees memory allocated to an array of pointers
 * @array: pointer to the array of pointers to be freed
 */
void free_memory(char **array)
{
    int i = 0;

    while (array[i] != NULL)
        free(array[i++]);

    free(array);
}

/**
 * shell_loop - the main loop of the shell
 *
 * Return: void
 */
void shell_loop(void)
{
    char *input = NULL;
    char **commands = NULL;

    while (1)
    {
        printf("$ ");
        input = read_input();

        if (input == NULL)
            continue;

        commands = split_commands(input);
        if (commands == NULL)
            continue;

        execute_commands(commands);

        free_memory(commands);
        free(input);
    }
}
