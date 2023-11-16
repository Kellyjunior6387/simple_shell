#include "main.h"

/**
 * to_strn - Converts an int to a string
 * @num: Integer to be converted to string
 * Return: Pointer to a string otherwise NULL
 */

char *to_strn(long int num)
{
    long int iterator, divisor = num, is_negative = num;
    char *result_str;

    if (num < 0)
    {
        divisor *= -1;
        for (iterator = 0; divisor > 0; iterator++)
        {
            divisor /= 10;
        }
        iterator++;
        num *= -1;
    }
    else
    {
        for (iterator = 0; divisor > 0; iterator++)
        {
            divisor /= 10;
        }
    }

    result_str = malloc((iterator + 1) * sizeof(char));

    if (result_str == NULL)
    {
        free(result_str);
        return NULL;
    }

    *(result_str + iterator) = '\0';
    iterator--;

    for (; iterator >= 0; iterator--)
    {
        *(result_str + iterator) = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative < 0)
    {
        result_str[0] = '-';
    }

    return result_str;
}

