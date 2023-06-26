#include "main.h"
/**
 * handle_print -this function is responsible for printing an argument based on its type.
 * @fmt:This parameter represents a formatted string in which the arguments are to be *printed
 * @list:This parameter represents a list of arguments to be printed
 * @ind:This parameter represents an index parameter
 * @buffer:This parameter represents a buffer array used to handle the printing operation.
 * @flags: This parameter is used to calculate the active flags for the printing operation.
 * @width:: This parameter represents the width specification for the printing operation.
 * @precision:This parameter represents the precision specification for the printing    *operation
 * @size:This parameter represents the size specifier for the printing operation.
 * Return: function returns either 1 or 2.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int index, num_chars_printed = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (index = 0; fmt_types[index].fmt != '\0'; index++)
		if (fmt[*ind] == fmt_types[index].fmt)
			return (fmt_types[index].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[index].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		num_chars_printed += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			num_chars_printed += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		num_chars_printed += write(1, &fmt[*ind], 1);
		return (num_chars_printed);
	}
	return (printed_chars);
}

