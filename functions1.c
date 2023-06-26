#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - function is responsible for printing an unsigned number.
 * @types: his parameter represents a list of arguments passed to the function
 * @buffer:This parameter refers to a buffer array used for handling the print
 * operation
 * @flags:This parameter is used to calculate the active flags for the print
 * operation
 * @width:This parameter specifies the width of the unsigned number to be
 * printed
 * @precision: This parameter specifies the precision of the unsigned number to
 * be printed.
 * @size:This parameter represents the size specifier for the print operation.
 * Return:function returns the number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = BUFF_SIZE - 2;
	unsigned long int current_num = va_arg(types, unsigned long int);

	current_num = convert_size_unsgnd(current_num, size);

	if (current_num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (current_num > 0)
	{
		buffer[index--] = (current_num % 10) + '0';
		current_num /= 10;
	}

	index++;

	return (write_unsgnd(0, index, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal -this function is responsible for printing an unsigned number in
 * octal *notation.
 * @types: his parameter represents a list of arguments passed to the function
 * @buffer: This parameter refers to a buffer array used for handling the print
 * operation
 * @flags: This parameter is used to calculate the active flags for the print
 * operation
 * @width:This parameter specifies the width of the octal number to be printed
 * @precision:This parameter specifies the precision of the octal number to
 * be printed
 * @size:This parameter represents the size specifier for the print operation.
 * Return:the function returns the number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int index = BUFF_SIZE - 2;
	unsigned long int current_num = va_arg(types, unsigned long int);
	unsigned long int original_num = current_num;

	UNUSED(width);

	current_num = convert_size_unsgnd(current_num, size);

	if (current_num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (current_num > 0)
	{
		buffer[index--] = (current_num % 8) + '0';
		current_num /= 8;
	}

	if (flags & F_HASH && original_num != 0)
		buffer[index--] = '0';

	index++;

	return (write_unsgnd(0, index, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal -this function is responsible for printing an unsigned
 * number in *hexadecimal notation.
 * @types: This parameter represents a list of arguments passed to the function
 * @buffer: This parameter refers to a buffer array used for handling the print
 * operation
 * @flags:This parameter is used to calculate the active flags for the print
 * operation.
 * @width:This parameter specifies the width of the hexadecimal number to be
 * printed.
 * @precision:This parameter specifies the precision of the hexadecimal number
 * to be  *printed.
 * @size:This parameter represents the size specifier for the print operation
 * Return: function returns the number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper -this  Function  prints an unsigned number in
 * upper hexadecimal notation
 * @types: This parameter represents a list of arguments passed to the function
 * @buffer: This parameter refers to a buffer array used for handling the print
 * operation
 * @flags:This parameter is used to calculate the active flags for the print
 * operation.
 * @width:This parameter specifies the width of the hexadecimal number to be
 * printed.
 * @precision:This parameter specifies the precision of the hexadecimal number
 * to be printed.
 * @size:This parameter represents the size specifier for the print operation.
 * Return: function returns the number of characters printed.
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa -his function is responsible for printing a hexadecimal number in
 *  either *lower or upper case.
 * @types: This parameter represents a list of arguments passed to the function
 * @map_to:This parameter represents an array of values used to map the number
 * towhich likely determines whether the hexadecimal number is printed in lower
 * or upper case.
 * @buffer:This parameter refers to a buffer array used for handling the print
 * operation.
 * @flags:This parameter is used to calculate the active flags for the print
 * operation.
 * @flag_ch:This parameter is used to calculate additional active flags.
 * @width:This parameter specifies the width of the hexadecimal number to be
 * printed.
 * @precision:This parameter specifies the width of the hexadecimal number to
 * be printed.
 * @size: This parameter represents the size specifier for the print operation.
 * Return: function returns the number of characters printed.
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int index = BUFF_SIZE - 2;
	unsigned long int current_num = va_arg(types, unsigned long int);
	unsigned long int origanal_num = current_num;

	UNUSED(width);

	current_num = convert_size_unsgnd(current_num, size);

	if (current_num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (current_num > 0)
	{
		buffer[index--] = map_to[current_num % 16];
		current_num /= 16;
	}

	if (flags & F_HASH && origanal_num != 0)
	{
		buffer[index--] = flag_ch;
		buffer[index--] = '0';
	}

	index++;

	return (write_unsgnd(0, index, buffer, flags, width, precision, size));
}

