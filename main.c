#include "monty.h"

/**
 * _getline - Reads a line of input from a stream.
 * @lineptr: Pointer to the buffer that will store the line.
 * @n: Pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * Return: The number of characters read, or -1 on failure or end of file.
 */
int _getline(char **lineptr, size_t *n, FILE *stream)
{
	int read;
	size_t len = 0;
	char *line = NULL;

	read = _getline(&line, n, stream);
	if (read != -1)
	{
		*lineptr = line;
		*n = len;
	}
	else
	{
		*lineptr = NULL;
		*n = 0;
		free(line);
	}

	return (read);
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	int read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	instruction_t instruction;
	char *opcode = strtok(line, " \t\n");

	while ((read = _getline(&line, &len, stdin)) != -1)
	{
		line_number++;
		if (!opcode || opcode[0] == '#')
			continue;

		instruction = get_instruction(opcode);
		if (instruction.opcode == NULL)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			free_stack(stack);
			free(line);
			exit(EXIT_FAILURE);
		}

		execute_instruction(instruction, &stack, line_number);
	}

	free_stack(stack);
	free(line);
	return (EXIT_SUCCESS);
}
