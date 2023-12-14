#include "shell.h"

/**
 * close_shell - closes the shell
 * @content: struct for future arguments
 *
 * Return: closes with given status (0) if content.argv[0] != "exit"
 */
int close_shell(info_t *content)
{
	int check_closed;

	if (content->argv[1])
	{
		check_closed = strToInt(content->argv[1]);
		if (check_closed == -1)
		{
			content->status = 2;
			putsError(content, "Not Allowed!");
			custom_puts(content->argv[1]);
			custom_putchar('\n');
			return (1);
		}
		content->errorNum = strToInt(content->argv[1]);
		return (-2);
	}
	content->errorNum = -1;
	return (-2);
}

/**
 * ch_dir - change directory
 * @content: struct for future arguments
 *
 * Return: Always 0.
 */
int ch_dir(info_t *content)
{
	char *s, *directory, buffer[1024];
	int rtrn_cd;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("getcwd fail\n");
	if (!content->argv[1])
	{
		directory = get_env(content, "HOME=");
		if (!directory)
			rtrn_cd = chdir((directory = get_env(content, "PWD=")) ? directory : "/");
		else
			rtrn_cd = chdir(directory);
	}
	else if (stringCmp(content->argv[1], "-") == 0)
	{
		if (!get_env(content, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(content, "OLDPWD=")), _putchar('\n');
		rtrn_cd = chdir((directory = get_env(content, "OLDPWD=")) ? directory : "/");
	}
	else
		rtrn_cd = chdir(content->argv[1]);
	if (rtrn_cd == -1)
	{
		putsError(content, "CD unsuccessful");
		custom_puts(content->argv[1]), custom_putchar('\n');
	}
	else
	{
		set_env(content, "OLDPWD", get_env(content, "PWD="));
		set_env(content, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_call - help call
 * @content: struct for future arguments
 *
 * Return: Always 0.
 */
int help_call(info_t *content)
{
	char **pp_arg;

	pp_arg = content->argv;
	_puts("Call for help relayed. Yet to be implemented.\n");
	if (0)
		_puts(*pp_arg);
	return (0);
}
