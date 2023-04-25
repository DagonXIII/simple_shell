#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;

/* Functions for the Shell */

/* execution_control */

int display_prompt(void);
char *read_user_input(void);
char *executable_path(char **av, char *PATH, char *copy);
int handle_builtin(char **av, char *buffer, int exit_status);
int fork_and_run(char **av, char *buffer, char *resolved_path);

/* string_manipulation */

char *duplicate_string(char *str);
int split_string(char *str);
int compare_strings(const char *s1, const char *s2);
char *concatenate_strings(char *dest, char *src);
int string_length(char *s);

/* create_command_arguments */

char **tokenize(char *buffer);
int split_path(char *str);
int compare_path_strings(const char *s1, const char *s2);
char *concatenate_path(char *tmp, char **av, char *tok);


/* helper_utilities */

char *get_env(const char *name);
int print_env(void);
void _puts(char *str);
int _putchar(char c);
char *set_memory(char *s, char b, unsigned int n);

/* more_advanced_functions */

void cd(char **args);

#endif /* MAIN_H */

