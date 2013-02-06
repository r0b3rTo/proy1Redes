/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: errors.c
   Contiene funciones para el manejo de errores de los programas bomba y centro.
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña  06-39990  
**/

#include "errors.h"


/*Funcion errorFatal
*    Parametros de entrada: Una cadena de caracteres con el mensaje de error.
*    Parametro de salida: Ninguno imprime por la salida estandar.
*    Toma el mensaje e imprime el programa del error y su mensaje, y termina el progama.*/
void errorFatal(char *mensaje) {
  fprintf(stderr, "%s: %s\n", program_invocation_short_name, mensaje);
  perror(program_invocation_short_name);
  fflush(stdout);
  exit(1);
}

/*Funcion mensajeError
*    Parametros de entrada: Una cadena de caracteres con el mensaje de error.
*    Parametro de salida: Ninguno imprime por la salida estandar.
*    Toma el mensaje e imprime el programa del error y su mensaje.*/
void mensajeError(char *mensaje) {
  fprintf(stderr, "%s: %s\n", program_invocation_short_name, mensaje);
  fflush(stdout);
}

/*
* Funcion terminar
*    Parametros de entrada: Una cadena de caracteres con el mensaje de error.
*    Parametro de salida: Ninguno imprime por la salida estandar.
*    Toma el mensaje, imprime el error y su mensaje, y termina el programa.
*/
void terminar(char *mensaje) {
  perror(mensaje);
  exit(1);
}
