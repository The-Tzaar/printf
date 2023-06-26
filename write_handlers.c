#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char -this function is used to handle the printing of a character.
 * @c:This parameter represents the character to be printed
 * @buffer:This parameter represents the buffer array used to handle the print operation
 * @flags:This parameter represents the active flags that are used for formatting or *controlling the printing process.
 * @width:This parameter represents the width specification, which determines the *minimum field width for the printed character.
 * @precision: This parameter represents the precision specification, which specifies *the maximum number of characters to be printed.
 * @size:This parameter represents the size specifier,
 *
 * Return:eturns the number of characters printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int index = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[index++] = c;
	buffer[index] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (index = 0; index < width - 1; index++)
			buffer[BUFF_SIZE - index - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - index - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - index - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number -this function is used to print a number.
 * @is_negative:This parameter indicates whether the number is negative or not
 * @ind:This parameter represents the index of the number in the formatted string..
 * @buffer: This parameter represents the buffer array used to handle the print *operation.
 * @flags:This parameter represents the active flags that are used for formatting 
 * @width:This parameter represents the width specification
 * @precision: This parameter represents the precision specification
 * @sizeThis parameter represents the size specifier
 *
 * Return:returns the number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - this function is used to write a number into a buffer.
 * @ind:This parameter represents the index at which the number starts on the buffer
 * @buffer:This parameter represents the buffer array used to write the number
 * @flags:This parameter represents the flags used for formatting the number
 * @width:This parameter represents the width specification for the number.
 * @prec:This parameter represents the precision specifier for the number.
 * @lengthThis parameter represents the length of the number.
 * @padd: This parameter represents the padding character
 * @extra_c: his parameter represents an extra character that may be associated with *the number
 * Return:returns the number of characters printed
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int index, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (index = 1; index < width - length + 1; index++)
			buffer[index] = padd;
		buffer[index] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], index - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], index - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], index - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd -this function is used to write an unsigned number.
 * @is_negative: This parameter is a number indicating whether the number is negative *or not. 
 * @ind:This parameter represents the index at which the number starts in the buffer.
 * @buffer:This parameter represents the array of characters, which likely serves as the 
*destination where the number will be written.
 * @flags: This parameter represents the flag specifiers used for formatting the number. 
 * @width: This parameter represents the width specifier for the number
 * @precision:This parameter represents the precision specifier for the number.
 * @size: This parameter represents the size specifier, which likely indicates the size or *data type of the number being written
 *
 * Return: the number of characters that were written
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, index = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (index = 0; index < width - length; index++)
			buffer[index] = padd;

		buffer[index] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], index));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], index) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - this function is used to write a memory address
 * @buffer: This parameter represents the array of characters
 * @ind: This parameter represents the index at which the number (memory address) *starts in the buffer.
 * @length:This parameter represents the length of the number (memory address).
 * @width:This parameter represents the width specifier for the number.
 * @flags: This parameter represents the flag specifier used for formatting the address
 * @padd: This parameter represents the character used for padding
 * @extra_c:This parameter represents an extra character that may be associated with *the address. 
 * @padd_start: : This parameter represents the index at which the padding should start *in the buffer
 *
 * Return: the number of characters that were written..
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int index;

	if (width > length)
	{
		for (index = 3; index < width - length + 3; index++)
			buffer[index] = padd;
		buffer[index] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], index - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], index - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], index - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

