#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

char **parse_arguments(char *line)
{
	static char *arguments[MAX_ARGS];
	int arg_index = 0;

	char *token = line;

	while (*line != '\0')
	{
		if (*line == ' ')
		{
			*line = '\0';
			arguments[arg_index++] = token;
			token = line + 1;
		}
	line++;
	}

	arguments[arg_index++] = token;
	arguments[arg_index] = NULL;

	return (arguments);
}

char *custom_getline()
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_pos;
	static ssize_t chars_read;

	char *line = malloc(sizeof(char) * BUFFER_SIZE);
	size_t line_pos = 0;
	int end_of_input = 0;

	while (1)
	{
		if (buffer_pos >= chars_read)
		{
			chars_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);

			if (chars_read <= 0)
		{
			end_of_input = 1;
			break;
		}
		buffer_pos = 0;
	}

	char c = buffer[buffer_pos++]
		;
	if (c == '\n')
	{
		line[line_pos] = '\0';
		break;
	}

	line[line_pos++] = c;

	if (line_pos >= BUFFER_SIZE - 1)
	{
		char *new_line = realloc(line, sizeof(char) * (line_pos + BUFFER_SIZE));

		if (new_line == NULL)
		{
			free(line);
			return (NULL);
		}

			line = new_line;
		}
	}

	if (end_of_input && line_pos == 0)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

int main(void)
{
	while (1)
	{
		printf("$ ");
		fflush(stdout);

	char *line = custom_getline();

	if (line == NULL)
	{
		break;
	}

	char **arguments = parse_arguments(line);

	printf("Command: %s\n", arguments[0]);

	int i = 0;

	while (arguments[i] != NULL)
	{
		printf("Argument %d: %s\n", i, arguments[i]);
		i++;
	}

	free(line);
	}

	return (0);
}
