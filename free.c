#include "main.h"

/**
 * free_struct - frees a 1D structure array grid
 * @data: pointer to a 1D structure array
 * Return: Nothing
 */
void free_struct(input_t *data)
{
    int i;

    for (i = 0; data->argv[i] != NULL; i++)
    {
        free(data->argv[i]);
    }
    
    free(data->argv[i]);
    free(data->argv);

    for (i = 0; data->envp[i] != NULL; i++)
    {
        free(data->envp[i]);
    }
    
    free(data->envp[i]);
    free(data->envp);
}

