#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/Execution.h"

#define INITIAL_BUFFER_SIZE 128

void *my_memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

void *my_calloc(size_t num_elements, size_t element_size) {
    // Calcul de la taille totale nécessaire en octets
    size_t total_size = num_elements * element_size;

    // Allocation de mémoire avec malloc
    void *ptr = malloc(total_size);

    if (ptr != NULL) {
        // Initialisation explicite de la mémoire allouée à zéro avec memset
        my_memset(ptr, 0, total_size);
    }

    return ptr;
}

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    // Initialisation des variables
    int ch;
    size_t index = 0;
    size_t buffer_size = *n;
    char *line = *lineptr;

    if (line == NULL || buffer_size == 0) {
        // Si le pointeur vers la ligne ou la taille du buffer est nul,
        // on alloue une taille initiale pour le buffer
        buffer_size = 128; // Taille initiale du buffer
        line = (char *)malloc(buffer_size * sizeof(char));
        if (line == NULL) {
            return -1; // Erreur d'allocation de mémoire
        }
    }

    while (1) {
        ch = getchar();

        // Si on atteint la fin de fichier ou un retour à la ligne, terminer la ligne
        if (ch == EOF || ch == '\n') {
            line[index] = '\0';
            break;
        }

        // Stocker le caractère dans la ligne
        line[index] = (char)ch;
        index++;

        // Si on atteint la capacité maximale, agrandir le buffer
        if (index == buffer_size - 1) {
            buffer_size *= 2;
            char *temp = (char *)realloc(line, buffer_size * sizeof(char));
            if (temp == NULL) {
                return -1; // Erreur d'allocation de mémoire
            }
            line = temp;
        }
    }

    // Mettre à jour les valeurs des paramètres
    *lineptr = line;
    *n = buffer_size;

    return (ssize_t)index; // Retourne le nombre de caractères lus
}

/*int	main()
{
	char	*buffer = NULL;
	size_t	buf_size = 2048;

	// alloc buffer qui stockera la commande entree par l'user
	buffer = my_calloc(sizeof(char), buf_size);
	if (buffer == NULL) {
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}

	// ecriture d'un prompt
	write(1, "$> ", 3);

	// lecture de STDIN en boucle
	while (custom_getline(&buffer, &buf_size, stdin) > 0) {
		printf("cmd = %s\n", buffer);
		write(1, "$> ", 3);
	}

	printf("Bye \n");
	free(buffer);
}*/
/*
Output :

$> ls -la
cmd = ls -la

$> cd ~/
cmd = cd ~/

$> pwd
cmd = pwd

$> Bye 
*/