#include "main.h"

/**
 * get_precision -this function is responsible for calculating
 * the precision for printing.
 * @format:This parameter represents a formatted string in which
 * the arguments are to * be printed
 * @i:This parameter represents an index parameter
 * @list: This parameter represents a list of arguments to be printed
 *
 * Return:function returns the calculated precision
 */

int get_precision(const char *format, int *i, va_list list)
{
	int curr_index = *i + 1;
	int num_digits = -1;

	if (format[curr_index] != '.')
		return (num_digits);

	num_digits = 0;

	for (curr_index += 1; format[curr_index] != '\0'; curr_index++)
	{
		if (is_digit(format[curr_index]))
		{
			num_digits *= 10;
			num_digits += format[curr_index] - '0';
		}
		else if (format[curr_index] == '*')
		{
			curr_index++;
			num_digits = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_index - 1;

	return (num_digits);
}

