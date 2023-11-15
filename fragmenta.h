/*
 * PROGRAMA: fragmenta
 * FICHERO: fragmenta.h
 * VERSION: 1.0.0
 * HISTÓRICO:
 * 		Creado por: Martín Sotelo Aguirre el 04/10/2023
 * DESCRIPCIÓN:
 *      Contiene dos funciones:
 *          -Fragmenta: Que guarda la entrada en la MiniShell en un array
 *          -Borrarg: Vacía el array
 */

/*
 * Especificaciones de las funciones
 */

/*
 * ACCION: fragmenta
 * ENTRADA: un puntero a un caracter constante
 * MODIFICA: el puntero al array
 */
/*
 * ACCION: borrarg
 * ENTRADA: un puntero a un puntero a un caracter
 * MODIFICA: el array y el entero
 */

/*Contenido de fragmenta.h */
char **fragmenta(const char*);
void borrarg(char **arg);
/* Fin de fragmenta.h */
