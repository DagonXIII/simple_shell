#include "main.h"
/**
 * cd - change the current working directory of the process
 * @path: the path to the directory to change to
 *
 * Return: 0 on success, -1 on failure
 */
void cd(char **args)
{
	char *path;

	if (args == NULL || args[0] == NULL)
		path = get_env("HOME");
	else if (strcmp(args[0], "-") == 0)
	{
		path = get_env("OLDPWD");
		if (path == NULL)
			path = getcwd(NULL, 0);
		printf("%s\n", path);
	}
	else
		path = args[0];

	if (chdir(path) == -1)
		perror("cd");

	get_env("OLDPWD", get_env("PWD"));
	set_env("PWD", getcwd(NULL, 0));
}
