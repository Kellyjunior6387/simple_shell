#include "main.h"

/**
 * tokenizer - returns the number of directories above the dir
 * @dir: relative path to dir/file
 * Return: number of directories above cwd
 */
int tokenizer(char *dir)
{
    int i, ln = 0;

    for (i = 0; dir[i] != '\0'; i++)
    {
        if (dir[i] == '.' && dir[i + 1] == '.' && dir[i + 2] == '/')
            ln++;
    }

    return ln;
}

/**
 * name_tokenizer - extracts the location of the file or directory
 * discarding relative path
 * @dir: relative path to directory/file
 * Return: location of file or dir
 */
char *name_tokenizer(char *dir)
{
    int i = 0, len, k = 0;
    char *name;

    while (dir[i] != '\0' && (dir[i] == '.' || dir[i] == '/'))
        i++;
    
    len = _strlen(&dir[i]);
    name = malloc(sizeof(char) * (len + 1));

    if (name == NULL)
        return NULL;

    for (k = 0; k < len; k++)
    {
        name[k] = dir[i];
        i++;
    }

    name[k] = '\0';

    return name;
}

/**
 * free_pointers - free used pointers
 * @s1: string1
 * @s2: string2
 * @s3: string3
 * Return: nothing
 */
void free_pointers(char *s1, char *s2, char *s3)
{
    free(s1);
    free(s2);
    free(s3);
}

/**
 * absolute_path - generates absolute directory path from a relative path
 * @cwd: current working dir
 * @dir: relative dir path
 * Return: absolute path to a directory/file
 */
char *absolute_path(char *cwd, char *dir)
{
    char *str2, *name, *temp, *temp2, *str3, *path, *delim = "/";
    int i = 0, len = 0, ln = 0;

    str2 = malloc(sizeof(char) * (_strlen(cwd) + 1));
    
    if (str2 == NULL)
        return NULL;

    _strcpy(str2, cwd);

    str3 = malloc(sizeof(char) * (_strlen(cwd) + 1));

    if (str3 == NULL)
    {
        free(str2);
        return NULL;
    }

    _strcpy(str3, cwd);

    temp = strtok(str3, delim);

    while (temp)
    {
        len += _strlen(temp);
        len++;
        temp = strtok(NULL, delim);
        i++;
    }

    ln = tokenizer(dir);
    name = name_tokenizer(dir);

    if (name == NULL)
    {
        free_pointers(str2, str3, name);
        return NULL;
    }

    path = malloc(sizeof(char) * (len + _strlen(name) + 1));

    if (path == NULL)
    {
        free_pointers(str2, str3, name);
        return NULL;
    }

    temp2 = strtok(str2, delim);
    path[0] = '/';
    path[1] = '\0';

    for (; ln < i; ln++)
    {
        _strcat(path, temp2);
        _strcat(path, "/");
        temp2 = strtok(NULL, delim);
    }
    _strcat(path, name);
    free_pointers(str2, str3, name);
    return path;
}

