#include "main.h"

/**
 * get_flags - this function is responsible for calculating active flags.
 * @format:This parameter represents a formatted string in which the
 * arguments are to * be printed, t is used as input for the function
 * to determine the active flags.
 * @i:This parameter represents an index parameter, likely used within
 * the function to L* *access specific elements or characters in the
 * formatted string.
 * Return: the function returns the calculated flags
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int loop_counter, current_index;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_index = *i + 1; format[current_index] != '\0'; current_index++)
	{
		for (loop_counter = 0; FLAGS_CH[loop_counter] != '\0'; loop_counter++)
			if (format[current_index] == FLAGS_CH[loop_counter])
			{
				flags |= FLAGS_ARR[loop_counter];
				break;
			}

		if (FLAGS_CH[loop_counter] == 0)
			break;
	}

	*i = current_index - 1;

	return (flags);
}


