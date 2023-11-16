#include "main.h"
/**
 * wexit - returns the exit status of child process
 * @status: exit status or termination status of child process
 * Return: exit status value
 */
int wexit(int status, input_t *cmd)
{
	if (WIFEXITED(status))
	{
		if (isatty(STDIN_FILENO))
			return (WEXITSTATUS(status));
		free_struct(cmd);
		if (cmd->pathFlag == 0)
			free(cmd->path);
		free(cmd);
		exit(WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}
/**
 * exec_section - implements a simple shell
 * @cmd: pointer to a struct
 * @av: program arguments
 * @num: tracks line number where error occurs
 * Return: Nothing
 */
int exec_section(input_t *cmd, char **av, int num)
{
	pid_t pid1;
	int i, wstatus;
	char *snum;

	if (cmd->path == NULL || cmd->envp == NULL)
	{
		if (!isatty(STDIN_FILENO))
			exit(127);
		return (127); }
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		return (2); }
	if (pid1 > 0)
	{
		waitpid(pid1, &wstatus, 0);
		return (wexit(wstatus, cmd)); }
		wait(NULL);
	if (pid1 == 0)
	{
		if (execve(cmd->path, cmd->argv, cmd->envp) == -1)
		{
			snum = to_strn(num);
			write(2, av[0], _strlen(av[0]));
			write(2, ": ", 2);
			write(2, snum, (_strlen(snum)));
			write(2, ": ", 2);
			for (i = 0; cmd->argv[i] != NULL; i++)
			{
				write(2, cmd->argv[i], _strlen(cmd->argv[i]));
				write(2, " ", 1);
			}
			write(2, ": not found\n", _strlen(": not found\n"));
			free(snum);
			return (2);
		}
	}
	return (0);
}
/**
 * main - implements a simple shell
 * @ac: argument count
 * @av: arguments array
 * @envp: environment variables
 * Return: EXIT_SUCCESS
 */
int main(int ac, char **av, char **envp)
{
	input_t *cmd;
	int prompt_no = 1;

	(void)ac;
	(void)av;

	while (1)
	{
		cmd = get_input(envp);
		if (cmd == NULL)
			continue;
		if (_strncmp(cmd->argv[0], "exit", 4) == 0)
			_exiting(cmd);
		/*if (_strncmp(cmd->argv[0], "env", 3) == 0)
			_env(cmd, envp);*/
		else if (_strncmp(cmd->argv[0], "cd", 2) == 0)
		{
			_chdir(cmd);
		}
		else
			exec_section(cmd, av, prompt_no);

		/*free(args);*/
		free_struct(cmd);
		if (cmd->pathFlag == 0)
			free(cmd->path);
		free(cmd);
		prompt_no++;
	}

	return (EXIT_SUCCESS);
}
