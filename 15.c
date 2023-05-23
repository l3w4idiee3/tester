#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
	printf("Enter a command: ");
	fgets(command, MAX_COMMAND_LENGTH, stdin);

	command[strcspn(command, "\n")] = '\0';

	if (strlen(command) == 0 || command[0] == '#')
	{
		continue;
	}
		system(command);
	}

	return (0);
}
