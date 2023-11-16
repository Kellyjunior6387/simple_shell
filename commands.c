#include "main.h"

/**
 * com_sort - sorts command names
 * @name: name of command
 * Return: path to the respective command program
 */
char *com_sort(char *name)
{
    char *temp = NULL, cwd[1024], *cmd_name, *cmd = NULL;

    temp = getcwd(cwd, sizeof(cwd));

    temp = malloc(sizeof(char) * (_strlen(cwd) + 1));

    if (temp == NULL)
        return NULL;

    _strcpy(temp, cwd);

    if (_strncmp(name, "../", 3) == 0 ||
        _strncmp(name, "./../", 5) == 0)
    {
        free(temp);
        return absolute_path(cwd, name);
    }

    /* generate the full path to the command executable */
    cmd_name = strtok(name, ".~/");
    cmd = malloc(sizeof(char) * (_strlen(name) + _strlen(temp) + 2));

    if (cmd != NULL)
    {
        _strcpy(cmd, temp);
        _strcat(cmd, "/");
        _strcat(cmd, cmd_name);
        _strcat(cmd, "\0");
    }

    free(temp);
    return cmd;
}

/**
 * com_path - returns the pathname to the command
 * @cmd_name: name of command
 * Return: pathname to command
 */
char *com_path(char *cmd_name)
{
    char *cmd, *str, *name, *path = "/bin/";

    if (_strncmp(cmd_name, "./", 2) == 0 ||
        _strncmp(cmd_name, "../", 3) == 0)
    {
        return com_sort(cmd_name);
    }
    else if (cmd_name[0] == '/')
    {
        name = strtok(cmd_name, " ");
        cmd = malloc(sizeof(char) * (_strlen(name) + 1));
        _strcpy(cmd, name);
    }
    else
    {
        str = com_search(cmd_name);

        if (str != NULL)
            free(str);
        else
            return NULL;

        cmd = malloc(sizeof(char) * (_strlen(cmd_name) + _strlen(path) + 1));

        if (cmd == NULL)
            perror("malloc in com_path failed\n");

        _strcpy(cmd, path);
        _strcat(cmd, cmd_name);
    }

    return cmd;
}

