/*
 * PROGRAMA: fragmenta
 * FICHERO: fragmenta.c
 * VERSION: 1.0.0
 * HISTÓRICO:
 * 		Creado por: Martín Sotelo Aguirre el 04/10/2023
 * DESCRIPCIÓN:
 * 		Este programa fragmenta una cadena de palabras y guarda cada palabra en una celda de un array

 */

#include "fragmenta.h"
#include <string.h>
#include <stdlib.h>

int calculaTamano(const char* cadena);

char **fragmenta(const char *cadena){
    //Definimos las variables
    char** array;
    char *copiaCadena;
    char* comando;
    char delimitador[] = " ";
    int tamano, i;

    //Calculo el tamaño de la cadena
    tamano = calculaTamano(cadena);

    array = (char**)malloc((tamano)*sizeof(char*));    //Creo mi array con el tamaño calculador y uno más para el NULL
    comando = strtok((char*)cadena, delimitador);
    i = 0;
    while(comando != NULL){     //Relleno cada celda con un comando/token teniendo en cuenta lo que ocupa cada comando
        array[i] = (char*)malloc(sizeof(char)*(strlen(comando)+1));
        strcpy(array[i],comando);
        i++;
        comando = strtok(NULL,delimitador);
    }
    array[i] = NULL;    //Leemos el NULO para luego indicar el final del array
    return(array);
}

void borrarg(char **arg){
    int i = 0;
    //Liberamos
    while(arg[i] != NULL){
        free(arg[i]);
        i = i + 1;
    }
    free(arg);
}

int calculaTamano(const char* cadena){
    char* comando;
    char* copiaCadena;
    int tamano = 1;
    char delimitador[] = " ";

    copiaCadena = (char*)malloc((strlen(cadena)+1)*sizeof(char));
    strcpy(copiaCadena, cadena);    //Hago copia de mi cadena para evitar modificaciones de la original

    comando = strtok(copiaCadena, delimitador);
    tamano++;
    comando = strtok(NULL, delimitador);//Leo un token
    while (comando != NULL){
        tamano++;
        comando = strtok(NULL, delimitador);
        //ponemos NULL, porque strtok devuelve la cadena en la posición que toca leer, si pongo otra cosa que no sea NULL, cogerá el mismo comando todo el rato.
    }
    return tamano;
}
