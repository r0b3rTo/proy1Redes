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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <pthread.h>

//Includes relacionados a las funciones de red
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//Include sobre el manejo de errores
#include "errors.h"

//Definición de constantes
#define PROGRAM_NAME "centro"
#define TAMANIO_COLA 5
#define TIEMPO_SIMULACION 480

/*Tipo option 
 *Permite obtener las opciones de llamada del programa.
*/
static struct option long_options[] = {
   {"cp", required_argument, 0, 'c'},
   {0, 0, 0, 0}
};

/* Tipo servidor
 * Contiene los parámetros que definen el funcionamiento del servidor.
 * Dichos parámetros son:
 * nombreCentro:      Nombre del centro de distribución
 * capacidadMaxima:   Capacidad máxima en litros
 * inventario:        Inventario actual
 * tiempo:            Tiempo de respuesta en minutos
 * suministro:        Suministro promedio en litros por minuto
 * puerto:            Puerto por el cual escuchará peticiones
 * tiempoSimulacion:  Lapso de tiempo transcurrido de la simulación
*/
typedef struct servidor{
   char* nombreCentro ;
   int capacidadMaxima;
   int inventario ;
   int tiempo ;
   int suministro ;
   int puerto ;
   int tiempoSimulacion ;
} Servidor;

/* Tipo parametros 
 * Contiene dos apuntadores a los parametros necesarios al momento de 
 * satisfacer las solicitudes de los clientes.
*/
typedef struct parametros{
   Servidor * servidor;
   int * descriptorSocket;
}Parametros;

pthread_mutex_t mutex_inventario;
pthread_mutex_t mutex_tiempoRespuesta;
