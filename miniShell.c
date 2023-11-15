/*
 * PROGRAMA: minishell
 * FICHERO: minishell.c
 * VERSION: 1.0.0
 * HISTÓRICO:
 * 		Creado por: Martín Sotelo Aguirre el 11/10/2023
 * DESCRIPCIÓN:
 * 		Este programa simula el funcionamiento de una shell

 */

#include "fragmenta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_LENGTH 100

/*
 * Especificaciones de las funciones
 */

/*
 * ACCION: tuberia "|"
 * ENTRADA: un array y un entero
 * MODIFICA: el array y el entero
 */
void tuberia(char** fragmentado, int i);
/*
 * ACCION: redirigePrincipio ">"
 * ENTRADA: un array y un entero
 * MODIFICA: el array y el entero
 */
void redirigePrincipio(char** fragmentado, int* i);
/*
 * ACCION: redirigeFinal ">>"
 * ENTRADA: un array y un entero
 * MODIFICA: el array y el entero
 */
void redirigeFinal(char** fragmentado, int* i);
/*
 * ACCION: cuentaLinPalCar "<"
 * ENTRADA: un array y un entero
 * MODIFICA: el array y el entero
 */
void cuentaLinPalCar(char** fragmentado, int* i);
/*
 * ACCION: manageError
 * ENTRADA: una string con el error y un valor para el error
 * DESCRIPCIÓN: Hay varias alternativas para expresar por pantalla
 * 	los errores, como errno o perror, pero prefiero dejar claro el error con un printf
 */
void manageError(char error[], int numeroDeError);

int main(){
	char** fragmentado;
	char input[MAX_INPUT_LENGTH];
    int pid, i;
    //char** comandos;
    //signal(SIGINT, exit);
	while(1){
		//Solicito una entrada al usuario
        printf("\nminishell\\>");
		//Espacio delante del scanf para evitar un loop infinito
		scanf(" %[^\n]",input);
		//Termino el programa si el usuario escribe exit
		if((strcmp(input, "exit") == 0)){
			return 0;
		}
		//Creo 2 procesos, porque el exec hace que se destruyan
		if((pid = fork()) == -1){
			manageError("Error al crear el PROCESO", -1);
		}
		if(pid == 0){
			//i es la posición del array, se actualizará con algunas llamadas a funciones
			i = 0;
			//Guardo en un array cada token
			fragmentado = fragmenta(input);
			//Casos a evaluar
			while(fragmentado[i] != NULL){
				//Para el comando: more kk.txt | grep hola, muestra el contenido de kk.txt que contenga hola
				if(strcmp(fragmentado[i],"|")== 0){
					tuberia(fragmentado, i);
				}
				//Para el comando: ls > fichero.txt, redirige la salida de ls a fichero.txt, sobreescribiendo
				else if(strcmp(fragmentado[i],">")== 0){
					redirigePrincipio(fragmentado, &i);
				}
				//Para el comando:  ls >> fichero.txt, redirige la salida de ls al final de fichero.txt
				else if(strcmp(fragmentado[i],">>")== 0){
					redirigeFinal(fragmentado, &i);
				}
				//Para el comando: wc < fichero.txt cuenta el número de líneas, palabras y caracteres en fichero.txt y los muestra por pantalla
				else if(strcmp(fragmentado[i],"<")== 0){
					cuentaLinPalCar(fragmentado, &i);
				}
				i++;
			}
			execvp(fragmentado[0], fragmentado);
			manageError("No existe el comando", 0);//El comando introducido no existe
		}
		else{
			//Espero a que termine el hijo, si el hijo termina antes de llegar al wait, el hijo se
			//convierte en un proceso zombie que se elimina al ejecutarse wait
			wait(NULL);
		}
	}
}

void tuberia(char** fragmentado, int i){
	int  tub[2], pid2;
	//Creamo la tuberia dado que tenemos "|"
	pipe(tub);
	char** mitadFragmentado;
	//Eliminamos de fragmentado "|"
	free(fragmentado[i]);
	fragmentado[i] = NULL;
	mitadFragmentado = &fragmentado[i + 1];
	if((pid2 = fork()) == -1){
		manageError("Error al crear el PROCESO",1);
	}
	//El hijo escribe
	else if(pid2 == 0){
		close(tub[0]);
		dup2(tub[1], STDOUT_FILENO);//La salida estándar es la tuberia
		close(tub[1]);
		execvp(fragmentado[0],fragmentado);//Muere el proceso que realiza el exec
		manageError("Error al ejecutar execvp", 2);
	}
	//El padre lee
	else{
		close(tub[1]);
		dup2(tub[0], STDIN_FILENO);//La entrada estándar es la tuberia
		close(tub[0]);
		execvp(mitadFragmentado[0],mitadFragmentado);//Muere el proceso que realiza el exec
		manageError("Error al ejecutar execvp", 3);
	}
}
void redirigePrincipio(char** fragmentado, int* i){
	int file;
	//Fichero abierto en SOLO ESCRITURA sobreescribiendo, si no existe lo crea.
	//Para obtener una memoria con todos los permisos para todos los usuarios pongo 0777
	file = open(fragmentado[*i + 1], O_CREAT|O_WRONLY, 0777);
	if(dup2(file, STDOUT_FILENO) == -1){//Hacemos que la salida ESTÁNDAR sea el fichero
		manageError("No se ha podido duplicar la salida estándar en el fichero.",4);
	}
	close(file);
	//Actualizo el array eliminando lo que ya no me hace falta
	free(fragmentado[*i]); //Elimina ">"
	free(fragmentado[*i + 1]); //Elimina de la linea de comandos el nombre del fichero
	fragmentado[*i] = NULL;
	(*i)++;
}
void redirigeFinal(char** fragmentado, int* i){
	int file;
	//Fichero abierto en SOLO ESCRITURA, en el que caso de que exista añado al final con O_APPEND(no sobreescribiendo), si no existe lo crea.
	//Para obtener una memoria con todos los permisos para todos los usuarios pongo 0777
	file = open(fragmentado[*i + 1], O_CREAT|O_WRONLY|O_APPEND);
	if(dup2(file, STDOUT_FILENO) == -1){//Hacemos que la salida ESTÁNDAR sea el fichero
		manageError("No se ha podido duplicar la salida estándar en el fichero.",5);
	}
	close(file);
	//Actualizo el array eliminando lo que ya no me hace falta
	free(fragmentado[*i]); //Elimina ">>"
	free(fragmentado[*i + 1]); //Elimina de la linea de comandos el nombre del fichero
	fragmentado[*i] = NULL;
	(*i)++;
}
void cuentaLinPalCar(char** fragmentado, int* i){
	int file;
	if((file = open(fragmentado[*i + 1], O_RDONLY)) == -1){//Fichero abierto en SOLO LECTURA
		manageError("NO se ha ABIERTO el fichero. Escriba el nombre correcto del fichero", 6);
	}
	if(dup2(file, STDIN_FILENO) == -1){//Hacemos que la salida ESTÁNDAR sea el fichero
		manageError("No se ha podido duplicar la salida estándar en el fichero.",7);
	}
	close(file);
	//Actualizo el array eliminando lo que ya no me hace falta
	free(fragmentado[*i]); //Elimina ">>"
	free(fragmentado[*i + 1]); //Elimina de la linea de comandos el nombre del fichero
	fragmentado[*i] = NULL;
	(*i)++;
}
void manageError(char error[], int numeroDeError){
	printf("\n/ERROR %d: <%s>\n", numeroDeError, error);
	exit(numeroDeError);
}
