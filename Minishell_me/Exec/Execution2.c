#include "../include/Execution.h"

size_t my_strlen(const char *str) 
{
    size_t length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

char *my_strcpy(char *dest, const char *src) {
    char *start = dest;

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; // Ajout du caractère nul à la fin de la chaîne destination

    return start; // Retourne un pointeur vers le début de la chaîne destination
}

char *my_strdup(const char *src) 
{
    size_t len = my_strlen(src) + 1; // Calcul de la taille de la chaîne source, y compris le caractère nul
    char *dst = (char *)malloc(len * sizeof(char)); // Allocation de mémoire pour la nouvelle chaîne

    if (dst == NULL) {
        return NULL; // En cas d'échec d'allocation de mémoire, retourne NULL
    }

    my_strcpy(dst, src); // Copie de la chaîne source dans la nouvelle chaîne

    return dst;
}

int my_strncmp(const char *s1, const char *s2, size_t n) {
    while (n > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
        n--;
    }

    if (n == 0) {
        return 0; // Si les n premiers caractères sont identiques
    } else {
        return (*s1 - *s2); // Différence ASCII des caractères qui diffèrent
    }
}


char *my_strcat(char *dest, const char *src) {
    char *start = dest;

    // Déplacer le pointeur de destination à la fin de la chaîne
    while (*dest != '\0') {
        dest++;
    }

    // Copier les caractères de la chaîne source à la fin de la chaîne destination
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; // Ajout du caractère nul à la fin de la chaîne concaténée

    return start; // Retourne un pointeur vers le début de la chaîne concaténée
}

 void	get_absolute_path(char **cmd)
{
	char	*path = my_strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL) // si le path est null, on cree un path
		path = my_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && my_strncmp(cmd[0], "./", 2) != 0) {

		// On split le path pour verifier ou ce trouve le binaire
		path_split = split(path, ":");
		free(path);
		path = NULL;

		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = (char *)calloc(sizeof(char), (my_strlen(path_split[i]) + 1 + my_strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			my_strcat(bin, path_split[i]);
			my_strcat(bin, "/");
			my_strcat(bin, cmd[0]);

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;

			// Nous sommes des gens propre :D
			free(bin);
			bin = NULL;
		}
		free_array(path_split);

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		free(cmd[0]);
		cmd[0] = bin;
	} else {
		free(path);
		path = NULL;
	}
}