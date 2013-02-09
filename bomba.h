/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: bomba.h
   Includes y definición de estructuras para el Programa bomba.
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña  06-39990  
**/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>

//Includes relacionados a las funciones de red
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//Include sobre el manejo de errores
#include "errors.h"

//Include sobre el manejo de la lista de Servidores
#include "ListaServidor.h"

//Definición de constantes
#define PROGRAM_NAME "bomba"
#define CARGA_GANDOLA 38000

/*Tipo option 
 *Permite obtener las opciones de llamada del programa.
*/
static struct option long_options[] = {
    {"cp", required_argument, 0, 'm'},
    {"fc", required_argument, 0, 'f'},
    {0, 0, 0, 0}
};

/*Tipo bomba
 *Contiene los parámetros que definen el funcionamiento de la bomba.
 *Dichos parámetros son:
 *nombreBomba:       Nombre de la bomba
 *capacidadMaxima:   Capacidad máxima en litros
 *inventario:        Inventario actual
 *consumo:           Consumo de gasolina en litros por minuto
 *ficheroCentros     Dirección del archivo con los datos de los centros
*/
typedef struct bomba{
   char* nombreBomba ;
   int capacidadMaxima;
   int inventario ;
   int consumo ;
   char* ficheroCentros ;
} Bomba;