#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void executeCommand(const char *command)
{
	char *arguments[MAX_ARGUMENTS];
	int argCount = 0;

	char *token = strtok((char)*command, " \t\n");

	while (token != NULL && argCount < MAX_ARGUMENTS - 1)
	{
		arguments[argCount++] = token;
		token = strtok(NULL, " \t\n");
	}
	arguments[argCount] = NULL;

	pid_t pid = fork();

	if (pid == 0)
	{
		execvp(arguments[0], arguments);
		printf("Command not found: %s\n", arguments[0]);
		exit(1);
	} else if (pid > 0)
	{
		int status;

		waitpid(pid, &status, 0);
	} else
	{
		printf("Failed to fork process\n");
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return (1);
	}

	const char *filename = argv[1];
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Failed to open file: %s\n", filename);
		return (1);
	}

	char command[MAX_COMMAND_LENGTH];

	while (fgets(command, sizeof(command), file))
	{
		executeCommand(command);
	}

	fclose(file);
	return (0);
}

