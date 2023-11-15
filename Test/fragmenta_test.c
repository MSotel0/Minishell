// Autor: Inigo Ezcurdia <inigofermin.ezcurdia@unavarra.es>
// Este programa tiene como único proposito comprobar el correcto funcionamiento de la libreria fragmenta a implementar por el estudiantado.
// Para compilar este programa es necesario proveer de la libreria fragmenta
//  Ejemplo: gcc -o fragmenta_test fragmenta_test.c fragmenta.o
// Este programa espera ser ejectuado proveiéndole de N argumentos. Calcula el tamaño en bytes de dichos argumentos para crear un string que los contenga separados por espacios.
// Este nuevo string recien creado, simula ser una entrada por teclado resultante de un scanf, de tal manera que podamos poner a prueba nuestra implementacion del comando fragmenta()
// Si el comando fragmenta correctamente el string, obtendremos un vector que recorrereremos y podremos imprimir por pantalla sin problemas.
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
