#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int ac, char **av)
{
	info_t content[] = { INFO_INIT };
	int file_des = 2;

	if (ac == 2)
	{
		file_des = open(av[1], O_RDONLY);
		if (file_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				custom_puts(av[0]);
				custom_puts(": 0: Failure to Open. ");
				custom_puts(av[1]);
				custom_putchar('\n');
				custom_putchar(BUF_ERASE);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		content->check_file_des = file_des;
	}
	content_env(content);
	getHistory(content);
	hsh(content, av);
	return (EXIT_SUCCESS);
}
