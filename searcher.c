#include "main.h"
#include <dirent.h>

/**
 * com_search - searches for the directory where the given command is located
 * @command_name: name of the program to search
 * Return: full path to the directory containing the program
 */
char *com_search(char *command_name)
{
    struct dirent *entry;
    DIR *directory;
    char *path_variable, *current_path, *path_segment, *temporary, *directory_name;

    path_variable = _getenv("PATH");
    current_path = malloc(sizeof(char) * (_strlen(path_variable) + 1));
    _strcpy(current_path, path_variable);

    path_segment = strtok(current_path, ":");
    while (path_segment != NULL)
    {
        directory = opendir(path_segment);
        if (directory != NULL)
        {
            while ((entry = readdir(directory)) != NULL)
            {
                directory_name = entry->d_name;
                if (_strncmp(command_name, directory_name, _strlen(directory_name)) == 0)
                {
                    closedir(directory);
                    temporary = malloc(sizeof(char) * (_strlen(path_segment) + 1));
                    _strcpy(temporary, path_segment);
                    free(current_path);
                    return temporary;
                }
            }
            closedir(directory);
        }
        path_segment = strtok(NULL, ":");
    }

    free(current_path);
    return NULL;
}

