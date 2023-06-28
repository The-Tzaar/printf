#include "main.h"

/**
 * @get_size -this function is responsible for
 * calculating the size to cast the argument.
 * @format:This parameter represents a
 * formatted string in which the arguments
 * are to be printed. It is used as input for the
 * function to determine the size specifier.
 * @i:This parameter represents an index parameter,
 *
 * Return : function returns the calculated size specifier
 */
int get_size(const char *format, int *i)
{
	int current_index = *i + 1;
	int size = 0;

	if (format[current_index] == 'l')
		size = S_LONG;
	else if (format[current_index] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = current_index - 1;
	else
		*i = current_index;

	return (size);
}

