/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: centro.h
   Includes y definición de estructuras para el Programa Servidor.
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña  06-39990  
**/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

//Includes relacionados a las funciones de red
#include <sys/socket.h>
#include <sys/types.h>

//Include sobre el manejo de errores
#include "errors.h"

//Definición de constantes
#define PROGRAM_NAME "centro"

/*Tipo option 
 *Permite obtener las opciones de llamada del programa.
*/
static struct option long_options[] = {
   {"cp", required_argument, 0, 'c'},
   {0, 0, 0, 0}
};

/*Tipo servidor
 *Contiene los parámetros que definen el funcionamiento del servidor.
 *Dichos parámetros son:
 *nombreCentro:      Nombre del centro de distribución
 *capacidadMaxima:   Capacidad máxima en litros
 *inventario:        Inventario actual
 *tiempo:            Tiempo de respuesta en minutos
 *suministro:        Suministro promedio en litros por minuto
 *puerto:            Puerto por el cual escuchará peticiones
*/
typedef struct servidor{
   char* nombreCentro ;
   int capacidadMaxima;
   int inventario ;
   int tiempo ;
   int suministro ;
   int puerto ;
} Servidor;
