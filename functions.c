#include "main.h"

/**
 * print_char - this function prints a chararector
 * @types: this is the list  of arguments
 * @buffer: this is buffer array to handle print
 * @flags: this will  calculates active flags
 * @width: this is the width
 * @precision:this is the  precision specification
 * @size: this is the size specifier
 * Return: num chars  printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - this function  prints a string
 * @types: This parameter represents a list of arguments passed to the function
 * @buffer:This parameter refers to a buffer array used for handling the
 * print operation.
 * @flags:  This parameter is used to calculate the active flags for the print
 * operation
 * @width: This parameter is used to get the width for the print operation.
 * @precision:This parameter specifies the precision for the print operation.
 * @size:This parameter represents the size specifier for the print operation.
 * Return: Num character  printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent -this function  prints a percent sign
 * @types:This parameter represents a list of arguments passed to the function
 * @buffer:This parameter refers to a buffer array used for handling the print
 * operation
 * @flags:This parameter is used to calculate the active flags for the print
 * operation.
 * @width:This parameter is used to get the width for the print operation.
 * @precision:This parameter specifies the precision for the print operation.
 * @size:This parameter represents the size specifier for the print operation.
 * Return: the number of characters printed.
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int -this function is responsible for printing an integer
 * @types:This parameter represents a list of arguments passed to the function
 * @buffer:This parameter refers to a buffer array used for handling the print
 * operation.
 * @flags:This parameter is used to calculate the active flags for the print
 * operation.
 * @width:This parameter specifies the width of the integer to be printed.
 * @precision: This parameter specifies the precision of the integer to be
 * printed.
 * @size: This parameter represents the size specifier for the print operation.
 * Return:the number of characters printed.
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary -this function is responsible for printing an unsigned number
 * in binary format.
 * @types:This parameter represents a list of arguments passed to the function
 * @buffer:This parameter refers to a buffer array used for handling the print
 * operation.
 * @flags:  This parameter is used to calculate the active flags for the print
 * operation.
 * @width:This parameter specifies the width of the binary number to be printed
 * @precision: This parameter specifies the precision of the binary number to
 * be printed.
 * @size: This parameter represents the size specifier for the print operation.
 * Return: the function returns the number of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int number, temp, index, num_bits;
	unsigned int a[32];
	int num_chars_printed;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	number = va_arg(types, unsigned int);
	temp = 2147483648; /* (2 ^ 31) */
	a[0] = number / temp;
	for (index = 1; index < 32; index++)
	{
		temp /= 2;
		a[index] = (number / temp) % 2;
	}
	for (index = 0, num_bits = 0, num_chars_printed = 0; index < 32; index++)
	{
		num_bits += a[index];
		if (num_bits || index == 31)
		{
			char z = '0' + a[index];

			write(1, &z, 1);
			num_chars_printed++;
		}
	}
	return (num_chars_printed);
}

