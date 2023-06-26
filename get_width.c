#include "main.h"

/**
 * get_width -this function is responsible for
 * calculating the width for printing.
 * @format:This parameter represents a
 * formatted string in which the arguments are to
 * be printed. It serves as input for the
 * function to determine the width.
 * @i:This parameter represents an index parameter.
 * @list:This parameter represents a
 * list of arguments to be printed.
 *
 * Return:function returns the width of the printed output
 */
int get_width(const char *format, int *i, va_list list)
{
	int current_index;
	int width = 0;

	for (current_index = *i + 1; format[current_index] != '\0'; current_index++)
	{
		if (is_digit(format[current_index]))
		{
			width *= 10;
			width += format[current_index] - '0';
		}
		else if (format[current_index] == '*')
		{
			current_index++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_index - 1;

	return (width);
}

