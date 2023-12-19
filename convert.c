#include "shell.h"

/**
 * strToInt - converts from string to integer
 * @s: string for conversion
 *
 * Return: 0 for NULL values, -1 on error
 */
int strToInt(char *s)
{
	int mag;
	unsigned long int soln;

	mag = 1;
	soln = 0;

	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		mag = -1;
		s++;
	}
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			if (soln > (INT_MAX / 10) || (soln == (INT_MAX / 10) && (*s - '0') > (INT_MAX % 10)))
				return (-1);
			soln = soln * 10 + (*s - '0');
		}
		else
			return (-1);
		s++;
	}
	return (mag * soln);
}

/**
 * putsError - prints an error message
 * @content: struct address
 * @estr: string of error message
 *
 * Return: error message.
 */
void putsError(info_t *content, char *estr)
{
	custom_puts(content->fname);
	custom_puts(": ");
	decimalPrint(content->line_count, STDERR_FILENO);
	custom_puts(": ");
	custom_puts(content->argv[0]);
	custom_puts(": ");
	custom_puts(estr);
}

/**
 * decimalPrint - prints numbers in base ten
 * @input: input
 * @file_des: File Descriptor
 *
 * Return: number of characters printed
 */
int decimalPrint(int input, int file_des)
{
	int (*__putchar)(char) = _putchar;
	int i, tally;
	unsigned int _abs_, presentVal;

	i = 0;
	tally = 0;;

	if (file_des == STDERR_FILENO)
		__putchar = custom_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		tally++;
	}
	else
		_abs_ = input;
	presentVal = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + presentVal / i);
			tally++;
		}
		presentVal %= i;
	}
	__putchar('0' + presentVal);
	tally++;
	return (tally);
}

/**
 * func_conversion - function for conversion
 * @num: number
 * @base: base
 * @prec_checks: argument prec_checks
 *
 * Return: the char pointer.
 */
char *func_conversion(long int num, int base, int prec_checks)
{
	static char *ptr_arr;
	static char buffer[50];
	char mag;
	char *ptr_char;
	unsigned long n;

	mag = 0;
	n = num;

	if (!(prec_checks & CHANGE_UNSIGNED) && num < 0)
	{
		n = -num;
		mag = '-';
	}
	ptr_arr = prec_checks & CHNG_LWRCS ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr_char = &buffer[49];
	*ptr_char = '\0';
	do {
		*--ptr_char = ptr_arr[n % base];
		n /= base;
	} while (n != 0);
	if (mag)
		*--ptr_char = mag;
	return (ptr_char);
}

/**
 * elimComent - modifies the address of a string
 * @memBuffer: string address
 *
 * Return: Always 0.
 */
void elimComent(char *memBuffer)
{
	int i;

	for (i = 0; memBuffer[i] != '\0'; i++)
		if (memBuffer[i] == '#' && (!i || memBuffer[i - 1] == ' '))
		{
			memBuffer[i] = '\0';
			break;
		}
}
