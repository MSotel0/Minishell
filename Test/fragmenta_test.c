// This program's sole purpose is to check the correct functioning of the fragmenta library to be implemented.
// To compile this program, it is necessary to provide the fragmenta library.
// Example: gcc -o fragmenta_test fragmenta_test.c fragmenta.o
// This program expects to be executed by providing it with N arguments. It calculates the size in bytes of these arguments to create a string that contains them separated by spaces.
// This newly created string simulates being a keyboard input resulting from a scanf, so that we can test our implementation of the fragmenta() command.
// If the fragmenta command correctly fragments the string, we will obtain a vector that we can traverse and print on the screen without any problems.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fragmenta.h"

int main(int argc, char **argv)
{

    if (argc <= 2) // Si no se provee de argumento al test, salgo inmediatamente
    return (-1);

    int arguments_size = 0; // Aquí acumularé el tamaño en bytes de todos los argumentos dados.

    int i = 1;
    while (argv[i] != NULL) // Recorro los argumentos dados hasta encontrar un NULL
    {
        arguments_size += sizeof(argv[i]); // Acumulo el tamaño del argumento de turno
        i++;
    }
    arguments_size += sizeof(" ") * (argc - 1); // También tengo en cuenta el tamaño en bytes de los espacios

    printf("Hay %d argumentos y ocupan %d bytes\n", argc - 1, arguments_size);
    char *test = (char *)malloc(arguments_size);
    printf("He reservado suficiente memoria para almacenar toda la frase.\n");
    
    i = 1;
    while (argv[i] != NULL)  // Recorro el array de argumentos concatenandolos
    {
        strcat(test, argv[i]);
        if (argv[i + 1] != NULL) // Si el siguiente elemento no es NULL, añado un espacio para separar las palabas.
            strcat(test, " ");
        i++;
    }
    printf("He construido la frase: \"%s\"\nProcedo a fragmentarla...\n",test);
    char **f = fragmenta(test);
    printf("He fragmentado la frase.\n");
    i = 0;
    while (f[i] != NULL)
    {
        printf("\tfragmento: %s\n", f[i]);
        i++;
    }
    printf("Procedo a liberar memoria mediante borrarg().\n");
    borrarg(f);
    printf("He liberado memoria.\nFIN!\n");
}
