/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: ListaServidor.c
   Contiene funciones para el manejo de una lista enlazada de
   Servidores, con su nombre, direccion, puerto y tiempo de respuesta.
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña  06-39990  
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListaServidor.h"


/*
* Funcion insertarServidor
*    Parametros de entrada: Una estructura de tipo ListaServidor que contiene 
*    Servidores, ademas de una cadena de caracteres con el nombre del servidor, 
*    un entero para su direccion, otro entero para su puerto y otro más para
*    su tiempo de respuesta.
*    Parametro de salida: Una estructura de tipo ListaServidor.
*    Recibe la listaServidores de la lista e inserta un nuevo Servidor.
*/
ListaServidor insertarServidor(ListaServidor listaServidores, char* nombre, char* direccion, int puerto, int tiempoRespuesta)
{ 
     ListaServidor nuevoServidor = NULL;
     char* auxnombre = (char*)malloc(sizeof(char)*100);
     if(auxnombre == NULL){
          terminar("Error de asignacion de memoria: " );
     }
     char* auxDireccion = (char*)malloc(sizeof(char)*100);
     if(auxDireccion == NULL){
          terminar("Error de asignacion de memoria: " );
     }
     int auxPuerto = puerto;
     int auxTiempoRespuesta = tiempoRespuesta;
     strcpy(auxnombre,nombre);
     strcpy(auxDireccion,direccion);
     nuevoServidor =(SERVIDOR*)malloc(sizeof(SERVIDOR));
     if(nuevoServidor == NULL){
          terminar("Error de asignacion de memoria: " );
     }
     nuevoServidor->nombre = auxnombre;   
     nuevoServidor->direccion = auxDireccion;
     nuevoServidor->puerto = auxPuerto;
     nuevoServidor->tiempoRespuesta = auxTiempoRespuesta;
     nuevoServidor-> siguiente = listaServidores; 
     listaServidores = nuevoServidor;
     
     return listaServidores;       
}

/* 
* Funcion insertarTiempoRespuesta
*    Parametros de entrada: Una estructura de tipo ListaServidor, ademas de 
*    una cadena de caracteres con el nombre y un entero con su tiempo de
*    respuesta.
*    Parametro de salida: Una estructura de tipo ListaServidor.
*    Busca en la lista de Servidores un servidor en específico y luego inserta
*    su tiempo de respuesta.
*/
ListaServidor insertarTiempoRespuesta(ListaServidor listaServidores, char* nombre, 
     int tiempoRespuesta)
{
    ListaServidor copiaListaServidores;
    copiaListaServidores=(SERVIDOR*)malloc(sizeof(SERVIDOR));
    if(copiaListaServidores == NULL){
         terminar("Error de asignacion de memoria: " );
    }
    copiaListaServidores = listaServidores;
    while(listaServidores != NULL && strcmp(listaServidores->nombre,nombre) != 0){
        listaServidores=listaServidores->siguiente;
    }
    if (listaServidores != NULL){ 
        listaServidores->tiempoRespuesta = tiempoRespuesta;
    }
    if(listaServidores == NULL){ 
        printf("El nombre del Centro de Distribución NO se encuentra en la lista de Centros válidos.\n");
    }
    return copiaListaServidores;
}


/*  
* Funcion buscarServidor
*    Parametros de entrada: Una estructura de tipo ListaServidor, ademas de una 
*    cadena de caracteres con el nombre del Servidor.
*    Parametro de salida: el Servidor buscado si se encuentra en la lista o
*    NULL si no se encuentra.
*    Busca en la lista y compara el nombre de cada Servidor, hasta encontrarlo
*    o se recorra toda  la lista.
*/
ListaServidor buscarServidor(ListaServidor listaServidores, char* nombre){
   ListaServidor servidorBuscado = NULL;
   while(listaServidores != NULL){
      if (strcmp(listaServidores->nombre,nombre) != 0){
          listaServidores = listaServidores->siguiente;
      } else {
          servidorBuscado = (SERVIDOR*)malloc(sizeof(SERVIDOR));
          if(servidorBuscado == NULL){
               terminar("Error de asignacion de memoria: " );
          }
          servidorBuscado->nombre = listaServidores->nombre;   
          servidorBuscado->direccion = listaServidores->direccion;
          servidorBuscado->puerto = listaServidores->puerto;
          servidorBuscado->tiempoRespuesta = listaServidores->tiempoRespuesta;
          return servidorBuscado;
      } 
   }
   return servidorBuscado;
}

/*
 * Funcion ordenarLista
 */
void ordenarLista(ListaServidor *listaServidores){
    ListaServidor copiaListaServidores = (SERVIDOR*)malloc(sizeof(SERVIDOR));
    if(copiaListaServidores == NULL){
         terminar("Error de asignacion de memoria: " );
    }
    copiaListaServidores = *listaServidores;
    ListaServidor aux, aux2, anterior;
    aux= *listaServidores;
    anterior = NULL;
    while(copiaListaServidores != NULL){
        aux2 = aux->siguiente;
        if(aux->tiempoRespuesta > aux2->tiempoRespuesta){
            aux->siguiente = aux2->siguiente;
            aux2->siguiente = aux;
            if(anterior == NULL){
                *listaServidores = aux2;
                anterior = *listaServidores;
            }
            else{
                anterior->siguiente = aux2;
                anterior = aux2;
            }
            aux = anterior->siguiente;
        }
        else{
            anterior = aux;
            aux = aux2;
        }
        copiaListaServidores = copiaListaServidores->siguiente;
    }
}

/* Funcion length
*    Parametros de entrada: Una estructura de tipo ListaServidor que contiene elementos
*    Parametro de salida: ninguno.
*    Recibe la cabeza de la lista y calcula la cantidad de elementos que la lista posee.
 */
int length(ListaServidor listaServidores){
   
   int longitud = 0;
   while(listaServidores != NULL){
      longitud= longitud + 1;
      listaServidores = listaServidores->siguiente;
   }
   return longitud;
}



/*   
* Funcion imprimirServidores
*    Parametros de entrada: Una estructura de tipo ListaServidor.
*    Parametro de salida: Ninguno, imprime la lista por salida estandar.
*    Recorre la lista imprimiendo por consola cada nombre de los Servidores.
*/
void imprimirServidores(ListaServidor listaServidores){

   while(listaServidores != NULL){
        printf("%s \n",listaServidores->nombre);
        listaServidores = listaServidores->siguiente;
   }
   printf("\n");
}