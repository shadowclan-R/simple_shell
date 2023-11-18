#include "shell.h"

/**
 * main - Main function for the shell.
 * @argc: Count of arguments.
 * @argv: Array of arguments.
 * @env: Environment variables.
 * Return: _exit value (0 by default).
 */
int main(int argc, char **argv, char **env)
{
	char *commandLine = NULL, **userCommand = NULL;
	int pathValue = 0, exitCode = 0, pathResult = 0;
	(void)argc;

	while (1)
	{
		commandLine = getCommandInput();
		if (commandLine)
		{
			pathValue++;
			userCommand = tokenizeString(commandLine);
			if (!userCommand)
			{
				free(commandLine);
				continue;
			}
			if ((!compareStrings(userCommand[0], "exit")) &&
					userCommand[1] == NULL)
				exitShell(userCommand, commandLine, exitCode);
			if (!compareStrings(userCommand[0], "env"))
				printEnvironment(env);
			else
			{
				pathResult = findExecutablePath(&userCommand[0], env);
				exitCode = executeCommand(userCommand, argv,
						env, commandLine, pathValue, pathResult);
				if (pathResult == 0)
					free(userCommand[0]);
			}
			if (compareStrings(userCommand[0], "setenv") == 0)
{
    if (userCommand[1] && userCommand[2])
    {
        if (setEnvVariable(userCommand[1], userCommand[2], env) == -1)
            fprintf(stderr, "Error: Unable to set environment variable\n");
    }
    else
    {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
    }
}
else if (compareStrings(userCommand[0], "unsetenv") == 0)
{
    if (userCommand[1])
    {
        if (unsetEnvVariable(userCommand[1], env) == -1)
            fprintf(stderr, "Error: Unable to unset environment variable\n");
    }
    else
    {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
    }
}
			free(userCommand);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(exitCode);
		}
		free(commandLine);
	}
	return (exitCode);
}
