#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - this Function prints the value of a pointer variable
 * @types: This parameter represents a list of arguments passed to the function
 * @buffer: This parameter refers to a buffer array used for handling the print
 * operation
 * @flags:This parameter is used to calculate the active flags for the
 * print operation
 * @width:This parameter specifies the width of the hexadecimal number to
 * be printed.
 * @precision:This parameter specifies the precision of the hexadecimal number
 * to be printed.
 * @size:This parameter represents the size specifier for the print operation.
 * Return: function returns the number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - this function  Prints ascii codes in hexa of non
 * printable chars
 * @types: This parameter represents a list of arguments passed to the function
 * @buffer: This parameter refers to a buffer array used for handling the
 * print operation
 * @flags:This parameter is used to calculate the active flags for the print
 * operation.
 * @width:This parameter specifies the width of the hexadecimal number to be
 * printed
 * @precision:This parameter specifies the precision of the hexadecimal number
 * to be printed.
 * @size:This parameter represents the size specifier for the print operation.
 * Return: function returns the number of characters printed.
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[index] != '\0')
	{
		if (is_printable(str[index]))
			buffer[index + offset] = str[index];
		else
			offset += append_hexa_code(str[index], buffer, index + offset);

		index++;
	}

	buffer[index + offset] = '\0';

	return (write(1, buffer, index + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - this Function Prints reverse string.
 * @types: This parameter represents a list of arguments passed to the function
 * @buffer: This parameter refers to a buffer array used for handling the print
 * operation
 * @flags:This parameter is used to calculate the active flags for the print
 * operation.
 * @width:This parameter specifies the width of the hexadecimal number to be
 * printed
 * @precision:This parameter specifies the precision of the hexadecimal number
 * to be printed.
 * @size:This parameter represents the size specifier for the print operation.
 * Return: function returns the number of characters printed.
 */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int index, printed_chars = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (index = 0; str[index]; index++)
		;

	for (index = index - 1; index >= 0; index--)
	{
		char z = str[index];

		write(1, &z, 1);
		printed_chars++;
	}
	return (printed_chars);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - this Function  Print a string in rot13.
  * @types: This parameter represents a list of arguments passed to the
  * function
 * @buffer: This parameter refers to a buffer array used for handling the
 * print operation
 * @flags:This parameter is used to calculate the active flags for the
 * print operation.
 * @width:This parameter specifies the width of the hexadecimal number to be
 * printed.
 * @precision:This parameter specifies the precision of the hexadecimal number
 * to be  *printed.
 * @size:This parameter represents the size specifier for the print operation.
 * Return: function returns the number of characters printed.
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char current_chars;
	char *str;
	unsigned int index, in_index;
	int printed_chars = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (index = 0; str[index]; index++)
	{
		for (in_index = 0; in[in_index]; in_index++)
		{
			if (in[in_index] == str[index])
			{
				current_chars = out[in_index];
				write(1, &current_chars, 1);
				printed_chars++;
				break;
			}
		}
		if (!in[in_index])
		{
			current_chars = str[index];
			write(1, &current_chars, 1);
			printed_chars++;
		}
	}
	return (printed_chars);
}

