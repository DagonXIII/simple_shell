#include "main.h"
/**
 * cd - change the current working directory of the process
 * @path: the path to the directory to change to
 *
 * Return: 0 on success, -1 on failure
 */
int cd(char *path)
{
	char *old_pwd = getcwd(NULL, 0);
	int ret;

	if (path == NULL || strcmp(path, "") == 0)
		path = get_env("HOME");
	if (strcmp(path, "-") == 0)
	{
		path = get_env("OLDPWD");
		if (path == NULL)
		{
			_puts("cd: OLDPWD not set\n");
			return (-1);
		}
		_puts(path);
		_puts("\n");
	}
	ret = chdir(path);
	if (ret == -1)
		perror("chdir");
	else
	{
		setenv("OLDPWD", old_pwd, 1);
		setenv("PWD", getcwd(NULL, 0), 1);
	}
	free(old_pwd);
	return (ret);
}
