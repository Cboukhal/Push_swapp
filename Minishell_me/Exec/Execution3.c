#include "../include/Execution.h"

int	main()
{
	char	*buffer = NULL;
	char	**cmd = NULL;
	size_t	buf_size = 2048;

	// alloc buffer qui stockera la commande entree par l'user
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL) {
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}

	// ecriture d'un prompt
	write(1, "$> ", 3);

	// lecture de STDIN en boucle
	while (custom_getline(&buffer, &buf_size, stdin) > 0) {
		cmd = split(buffer, " \n\t");
		get_absolute_path(cmd);

		if (cmd[0] == NULL)
			printf("Command not found\n");
		else
			exec_cmd(cmd);

		write(1, "$> ", 3);
		free_array(cmd);

	}

	printf("Bye \n");
	free(buffer);
	}
