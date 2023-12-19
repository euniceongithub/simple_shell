#include "shell.h"

builtin_table builtintbl[] = {
                {"exit", close_shell},
                {"env", print_curr_environ},
                {"help", help_call},
                {"history", sh_history},
                {"setenv", init_env},
                {"unsetenv", rem_env},
                {"cd", ch_dir},
                {"alias", ama_alias},
                {NULL, NULL}
        };

/**
 * hsh - main shell loop
 * @content: the parameter & return content struct
 * @av: the argument vector from main()
 *
 * Return: bult-in return value.
 */
int hsh(info_t *content, char **av)
{
	ssize_t x;
	int retVal;

	x = 0;
	retVal = 0;

	while (x != -1 && retVal != -2)
	{
		initInfo(content);
		if (check_interact(content))
			_puts("$ ");
		custom_putchar(BUF_ERASE);
		x = fetchContent(content);
		if (x != -1)
		{
			argInfo(content, av);
			retVal = locateCmd(content);
			if (retVal == -1)
				findCmd(content);
		}
		else if (check_interact(content))
			_putchar('\n');
		infoFree(content, 0);
	}
	printHistory(content);
	infoFree(content, 1);
	if (!check_interact(content) && content->status)
		exit(content->status);
	if (retVal == -2)
	{
		if (content->errorNum == -1)
			exit(content->status);
		exit(content->errorNum);
	}
	return (retVal);
}

/**
 * locateCmd - finds a builtin command
 * @content: content struct
 *
 * Return: ret_Val.
 */
int locateCmd(info_t *content)
{
	int i, ret_Val;

	ret_Val = -1;

	for (i = 0; builtintbl[i].type; i++)
		if (stringCmp(content->argv[0], builtintbl[i].type) == 0)
		{
			content->line_count++;
			ret_Val = builtintbl[i].func(content);
			break;
		}
	return (ret_Val);
}

/**
 * findCmd - finds a command in PATH
 * @content: content struct
 *
 * Return: void.
 */
void findCmd(info_t *content)
{
	char *path = NULL;
	int i, k;

	content->path = content->argv[0];
	if (content->linecount_prec_check == 1)
	{
		content->line_count++;
		content->linecount_prec_check = 0;
	}
	for (i = 0, k = 0; content->arg[i]; i++)
		if (!dm_check(content->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findCommand(content, get_env(content, "PATH="), content->argv[0]);
	if (path)
	{
		content->path = path;
		forkExec(content);
	}
	else
	{
		if ((check_interact(content) || get_env(content, "PATH=")
					|| content->argv[0][0] == '/') && execCheck(content, content->argv[0]))
			forkExec(content);
		else if (*(content->arg) != '\n')
		{
			content->status = 127;
			putsError(content, "missing\n");
		}
	}
}

/**
 * forkExec - forks an executable thread to run command
 * @content: content struct
 *
 * Return: void.
 */
void forkExec(info_t *content)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(content->path, content->argv, get_environ(content)) == -1)
		{
			infoFree(content, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(content->status));
		if (WIFEXITED(content->status))
		{
			content->status = WEXITSTATUS(content->status);
			if (content->status == 126)
				putsError(content, "No Access granted!\n");
		}
	}
}

