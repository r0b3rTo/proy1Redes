/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: bomba.c
   Código del Programa Cliente
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

//Include sobre el manejo de la lista de Servidores
#include "ListaServidor.h"


/*Funcion obtenerCentros
*    Parametros de entrada: Una estructura de tipo FILE.
*    Parametro de salida: Una cadena de caracteres con la respuesta del archivo.
*    Toma un apuntador a un file, y lo recorre concatenando la respuesta
*    a una cadena de caracteres.
*/
char* obtenerCentros(FILE *archivoCentros){
   char centrosInfo[100];
   char* centros = (char*)malloc(sizeof(char)*2056);
   if(centros == NULL){
      terminar("Error de asignacion de memoria: " );
   }
   char* aux;
   strcpy(centros," ");
   while(fgets(centrosInfo,sizeof(centrosInfo),archivoCentros) != NULL){
       aux = (char*)malloc(sizeof(char)*2056);
       if(aux == NULL){
         terminar("Error de asignacion de memoria: " );
       }
       strcpy(aux,centrosInfo);
       strcat(centros,centrosInfo);
   }
   return centros;
}

int main(int argc, char *argv[]){
   
   int flagN = 0;
   int flagCP = 0;
   int flagI = 0;
   int flagC = 0;
   int flagF = 0;

   int opt;
   int option_index;
   char* nombreBomba = "";
   int capacidadMaxima = -1;
   int inventario = -1;
   int consumoPromedio = -1;
   extern int optopt;

   static struct option long_options[] = {
      {"cp", required_argument, 0, 'm'},
      {"c", required_argument, 0, 'c'},
      {"fc", required_argument, 0, 'f'},
      {0, 0, 0, 0}
   };

   //Lectura de parámetros
   while((opt = getopt_long_only(argc, argv, "n:m:i:c:f", long_options, &option_index)) != -1){
      switch(opt){
         case 'n':
            if( strcmp(optarg,"") == 0 ){
               printf("Debe proveer un nombre de la Bomba distinto de vacío para el modificador 'n'.\n");
            }else{
               nombreBomba = optarg;
               flagN = 1;
               printf("Opción n con valor '%s'\n", nombreBomba);
            }           
            break;
         case 'i':
            inventario = atoi(optarg);
            if( (0 <= inventario) && (inventario <= capacidadMaxima) ){
               //BUG Está aceptando valores del modificador i que no son números
               flagI = 1;
               printf("Opción i con valor '%d'\n", inventario);
            }else{
               if(capacidadMaxima == -1){
                  //No se ha inicializado el valor del modificador 'cp'-> capacidadMaxima
                  printf("El modificador 'i' debe ir precedido por el modificador 'cp' y su valor corresponterminarnte.\n");
               }else{
                  //El valor inventario no se encuentra entre 0 y el valor de capacidadMaxima
                  printf("Debe proveer un valor para el modificador 'i' entre 0 y %d (Capacidad Máxima)\n", capacidadMaxima);
               }
            }
            break;
         case 'c':
            printf("Opción c con valor '%s'\n", optarg);
            break;
         case 'f':
            printf("Opción f con valor '%s'\n", optarg);
            break;
         case 'm':
            capacidadMaxima = atoi(optarg);
            if( (38000 <= capacidadMaxima) && (capacidadMaxima <= 3800000) ){
               flagC = 1;
               printf("Opción c con valor '%d'\n", capacidadMaxima);
            }else{              
               printf("Debe proveer un valor entre 38.000 y 3.800.000 para el modificador 'cp'.\n");
            }
            break;
         case ':':
            printf("Falta el valor del modificador '%c'.\n", optopt);
            break;
         case '?':
            printf("Opción desconocida %s\n", argv[optind-1]);
            break;
         default:         
            printf("?? getopt retornó código del character 0%o ??\n", opt);
            //usage(EXIT_FAILURE);      
      }
   }

}
