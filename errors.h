/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: errors.h
   Contiene la definición de los diferentes elementos para el manejo de errores de los programas
   bomba y centro.
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña  06-39990  
**/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef _ERRORS_H_
#define _ERROR_H_

extern char *program_invocation_name;
extern char *program_invocation_short_name;

extern void errorFatal(char *mensaje);
extern void mensajeError(char *mensaje);
extern void terminar(char*mensaje); 

#endif

