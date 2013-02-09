/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: ListaServidor.h
   Contiene la estructura de la ListaServidor, y cada uno de sus elementos.
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña  06-39990  
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Servidor {
   char* nombre;
   char* direccion;
   int puerto;
   int tiempoRespuesta;
   struct Servidor *siguiente; 
};

typedef struct Servidor SERVIDOR;/*por convencion en mayusculas */
typedef struct Servidor *ListaServidor;/*Direccion de inicio de la lista */

extern ListaServidor insertarServidor(ListaServidor, char*, char*,int,int);
extern ListaServidor insertarTiempoRespuesta(ListaServidor,char*,int);
extern ListaServidor buscarServidor(ListaServidor,char*);
extern ListaServidor ordenarLista(ListaServidor);
extern int length(ListaServidor);
extern void imprimirServidores(ListaServidor);