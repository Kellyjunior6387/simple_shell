#include "main.h"
/**
 * stderr_dump - redirects stderr message to /dev/null
 * Return: nothing
 */
void stderr_dump(void)
{
    int file_descriptor;

    file_descriptor = open("/dev/null", O_WRONLY);
    if (dup2(file_descriptor, STDERR_FILENO) != -1)
        close(file_descriptor);
}

/**
 * get_input - gets and processes input from stream
 * @environment: environment variables
 * Return: 1 if input is an absolute path to executable else 0
 */
input_t *get_input(char **environment)
{
    char **arguments = NULL, *input_string = NULL;
    int string_length = 10;
    input_t *temp_input;

    if (isatty(STDIN_FILENO))
    {
        if (write(STDOUT_FILENO, "$ ", _strlen("$ ")) == -1)
            exit(EXIT_FAILURE);
    }

    if (_getline(&input_string, &string_length, stdin) == 0)
    {
        stderr_dump();
        free(input_string);
        exit(0);
    }

    temp_input = malloc(sizeof(input_t));
    if (temp_input == NULL)
        return NULL;

    arguments = cmd_arg(input_string);
    if (arguments == NULL)
    {
        stderr_dump();
        free(temp_input);
        free(input_string);
        return NULL;
    }

    temp_input->argv = arguments;
    temp_input->pathFlag = 0;
    temp_input->path = com_path(temp_input->argv[0]);
    temp_input->envp = path_find(environment);

    free(input_string);

    return temp_input;
}

