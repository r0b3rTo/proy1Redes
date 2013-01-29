/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: centro.c
   Código del Programa Servidor
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña    
**/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

//Includes relacionados a las funciones de red
#include <sys/socket.h>
#include <sys/types.h>

/*usage
 *Descripción: uso apropiado del programa
 *Parámetro de entrada: status
*/

//void usage(){

//}

int main(int argc, char *argv[]){
   
   int flagN = 0;
   int flagC = 0;
   int flagI = 0;
   int flagT = 0;
   int flagS = 0;
   int flagP = 0;

   int opt;
   int option_index;
   char* nombreCentro = "";
   int capacidadMaxima = -1;
   int inventario = -1;
   int tiempo = -1;
   int suministro = -1;
   int puerto = -1;
   extern int optopt;

   static struct option long_options[] = {
      {"cp", required_argument, 0, 'c'},
      {0, 0, 0, 0}
   };

   //Lectura de parámetros
   while((opt = getopt_long_only(argc, argv, ":n:i:t:s:p:", long_options, &option_index)) != -1){
      switch(opt){
         case 'n':
            if( strcmp(optarg,"") == 0 ){
               printf("Debe proveer un nombre de Centro de Distribución distinto de vacío para el modificador 'n'.\n");
            }else{
               nombreCentro = optarg;
               flagN = 1;
               printf("Opción n con valor '%s'\n", nombreCentro);
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
                  printf("El modificador 'i' debe ir precedido por el modificador 'cp' y su valor correspondiente.\n");
               }else{
                  //El valor inventario no se encuentra entre 0 y el valor de capacidadMaxima
                  printf("Debe proveer un valor para el modificador 'i' entre 0 y %d (Capacidad Máxima)\n", capacidadMaxima);
               }
            }
            break;
         case 't':
            printf("Opción t con valor '%s'\n", optarg);
            break;
         case 's':
            printf("Opción s con valor '%s'\n", optarg);
            break;
         case 'p':
            printf("Opción p con valor '%s'\n", optarg);
            break;
         case 'c':
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
