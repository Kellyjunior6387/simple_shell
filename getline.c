#include "main.h"
#define INITIAL_BUFFER_SIZE 8000

/**
 * _getline - get line from stdin
 * @buffer_size: size of the initial buffer
 * @output_str: pointer to *string output
 * @input_stream: input *stream
 * Return: *string pointer
 */
int _getline(char **output_str, int *buffer_size, FILE *input_stream)
{
    int read_status, position = 0;
    char character;

    *buffer_size = INITIAL_BUFFER_SIZE;
    (void)*input_stream;
    *output_str = malloc(sizeof(char) * (*buffer_size));

    if (!*output_str)
    {
        return 0;
    }

    while (1)
    {
        read_status = read(STDIN_FILENO, &character, 1);

        if (read_status <= 0 || character == '\n')
        {
            (*output_str)[position] = '\0';
            return position;
        }
        else
        {
            (*output_str)[position] = character;
        }

        /* Reallocate memory */
        if (position >= (*buffer_size - 2))
        {
            *buffer_size += INITIAL_BUFFER_SIZE;
            *output_str = _realloc(*output_str, sizeof(char) * (*buffer_size), *buffer_size);

            if (*output_str == NULL)
            {
                return 0;
            }
        }

        position++;
    }

    return position;
}

