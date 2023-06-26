#include "main.h"

/**
 * is_printable -this function is used to evaluate whether a character is printable or not.
 * @c:This parameter represents the character to be evaluated.
 *
 * Return:function returns 1 if the character is printable, and 0 otherwise.
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code -this function is used to append ASCII characters in hexadecimal *code to a buffer.
 * @buffer:This parameter represents an array of characters, which likely serves 
* as the buffer to which the hexadecimal code is appended.
 * @i: This parameter represents the index at which to start appending
*the hexadecimal code in the buffe
 * @ascii_code:This parameter represents the ASCII code of the character to be *appended in hexadecimal form.
 * Return:function always returns 3.
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - this function is used to cast a number to a specified size.
 * @num:This parameter represents the number to be casted
 * @size: This parameter represents a number indicating the type or size to which the  *number should be casted.
 *
 * Return:function returns the casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd -this function is used to cast a number to a specified size, * *specifically an unsigned type.
 * @num:This parameter represents the number to be casted.
 * @size:This parameter represents a number indicating the type or size to which the *number should be casted.
 *
 * Return:function returns the casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

