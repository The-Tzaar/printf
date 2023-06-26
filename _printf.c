#include "main.h"


void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - this is a Print function
 * @format: this is the format
 * Return: Printed character.
 */
int _printf(const char *format, ...)
{
	int loop_counter, num_chars_printed = 0, total_printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (loop_counter = 0; format && format[loop_counter] != '\0'; loop_counter++)
	{
		if (format[loop_counter] != '%')
		{
			buffer[buff_ind++] = format[loop_counter];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[loop_counter], 1);*/
			total_printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &loop_counter);
			width = get_width(format, &loop_counter, list);
			precision = get_precision(format, &loop_counter, list);
			size = get_size(format, &loop_counter);
			++loop_counter;
			num_chars_printed = handle_print(format, &loop_counter, list, buffer,
			flags, width, precision, size);
			if (num_chars_printed == -1)
				return (-1);
			total_printed_chars += num_chars_printed;
		}
	}

	print_buffer(buffer, &buff_ind);


	va_end(list);


	return (total_printed_chars);
}


/**
 * print_buffer - this function prints  buffer content
 * @buffer: this is an array
 * @buff_ind:  represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);


	*buff_ind = 0;
}

