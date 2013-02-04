/**
   CI-4835 Redes de Computadoras
   Fecha: Enero 2013
   Proyecto I
   Archivo: centro.c
   Código del Programa Servidor
   Integrantes:
   Héctor López   05-38421
   Roberto Omaña  06-39990  
**/

#include "centro.h"

/* verificacionNombreCentro
 * Descripción: Procedimiento encargado de la verificación del valor del 
 * modificador -n.
 * En caso de que el valor no sea válido, imprime un mensaje de error.
 * En caso de que el valor sea válido, inicializa la variable correspondiente 
 * de la estructura Servidor y le coloca un valor TRUE a la variable flagN para 
 * indicar que se inicializó con éxito el parámetro.
 * Parámetros de entrada:
 * nombreCentro: apuntador a la cadena de caracteres que mantiene el valor del
 * nombre del centro de distribución en la estructura Servidor.
 * flagN: apuntador a la variable que indica si el valor del parámetro es 
 * correcto y por ende se modificó el valor de la estructura Servidor.
*/
void verificacionNombreCentro(char** nombreCentro, int *flagN){
   if( strcmp(optarg,"") == 0 ){
      printf("Debe proveer un nombre de Centro de Distribución distinto de vacío para el modificador '-n'.\n");
   }else{
      *nombreCentro = optarg;
      *flagN = 1;
   }           
}


/* verificacionEntero
 * Descripción: Procedimiento encargado de la verificación del valor de
 * los modificadores enteros.
 * En caso de que el valor no sea válido, imprime un mensaje de error.
 * En caso de que el valor sea válido, inicializa la variable correspondiente 
 * de la estructura Servidor y le coloca un valor TRUE a la variable flagParametro
 * para indicar que se inicializó con éxito el parámetro.
 * Parámetros de entrada:
*/
void verificacionEntero(int opt, int minimo, int maximo, int *variableServidor, int *flagParametro){
   float temp = -1.0;
   sscanf(optarg,"%f",&temp);
   int aux = (int) temp;
   float aux2 = temp-aux;

   if( (aux2 == 0) && (minimo <= temp) && (temp <= maximo) ){
      *variableServidor = temp;
      *flagParametro = 1;
   }else{
      if( (opt == 'i') && (maximo == -1) ){
         //No se ha inicializado el valor del modificador 'cp'-> capacidadMaxima
         printf("El modificador '-i' debe ir precedido por el modificador '-cp' y su valor correspondiente.\n");
      }else if( aux2 != 0 ){
         //Se introdujo un valor flotante
         if( opt == 'c' ){
            printf("El valor del modificador '-cp' debe ser entero.\n");      
         }else{
            printf("El valor del modificador '%c' debe ser entero.\n", opt);
         }
      }else{
         //El valor del parámetro no se encuentra entre el valor de mínimo y máximo
         if( opt == 'c' ){
            printf("Debe proveer un valor para el modificador '-cp' entre %d y %d.\n", minimo, maximo);
         }else{
            printf("Debe proveer un valor para el modificador '-%c' entre %d y %d.\n", opt, minimo, maximo);
         }
      }
   }
}


/* verificarParametrosFaltantes
 * Descripción: Procedimiento que verifica que todos los parámetros de 
 * invocación del programa se hayan inicializado de manera correcta.
 * Parámetros de entrada:
 * flagN
*/
void verificarParametrosFaltantes(int flagN, int flagC, int flagI, int flagT, int flagS, int flagP){
   if(!flagN){
      printf("Falta el modificador '-n' y su valor correspondiente.\n");
   } 
   if(!flagC){
      printf("Falta el modificador '-cp' y su valor correspondiente.\n");
   } 
   if(!flagI){
      printf("Falta el modificador '-i' y su valor correspondiente.\n");
   } 
   if(!flagT){
      printf("Falta el modificador '-t' y su valor correspondiente.\n");
   } 
   if(!flagS){
      printf("Falta el modificador '-s' y su valor correspondiente.\n");
   } 
   if(!flagP){
      printf("Falta el modificador '-p' y su valor correspondiente.\n");
   } 
   if(!flagN || !flagC || !flagI || !flagT || !flagS || !flagP){
      usage(EXIT_FAILURE);
   } 
}


/* manejarParametros
 * Descripción: Procedimiento que maneja apropiadamente los parámetros 
 * introducidos como modificadores a través de la línea de comandos.
 * Parámetros de entrada:
*/
void manejarParametros(int argc, char *argv[], Servidor* servidor){
   int flagN = 0;
   int flagC = 0;
   int flagI = 0;
   int flagT = 0;
   int flagS = 0;
   int flagP = 0;
   int opt;
   int option_index;
   extern int optopt;
   
   //Lectura de parámetros
   while((opt = getopt_long_only(argc, argv, ":n:i:t:s:p:", long_options, &option_index)) != -1){
      switch(opt){
         case 'n':
            verificacionNombreCentro(&servidor->nombreCentro, &flagN);
            break;
         case 'i':
            verificacionEntero(opt, 0, servidor->capacidadMaxima, &servidor->inventario, &flagI);
            break;
         case 't':
            verificacionEntero(opt, 0, 180, &servidor->tiempo, &flagT);
            break;
         case 's':
            verificacionEntero(opt, 0, 10000, &servidor->suministro, &flagS);
            break;
         case 'p':
            verificacionEntero(opt, 1, 65535, &servidor->puerto, &flagP);
            break;
         case 'c':
            verificacionEntero(opt, 38000, 3800000, &servidor->capacidadMaxima, &flagC);
            break;
         case ':':
            if(optopt == 'c'){
               printf("Falta el valor del modificador '-cp'.\n");
            }else{
               printf("Falta el valor del modificador '-%c'.\n", optopt);
            }
            break;
         case '?':
            printf("Opción desconocida %s\n", argv[optind-1]);
            break;
         default:         
            usage(EXIT_FAILURE);      
      }
   }
   verificarParametrosFaltantes(flagN, flagC, flagI, flagT, flagS, flagP);
}

/* usage
 * Descripción: Función que imprime en pantalla la manera apropiada de 
 * invocar el programa.
 * Parámetro de entrada: 
 * status: entero que indica si el programa termina con éxito o no.
*/
int usage (int status){                                                       
   if (status != EXIT_SUCCESS){                                                 
      printf ("Uso: %s -n nombreCentro -cp capacidadMaxima -i inventario -t tiempo -s suministro -p puerto\n", PROGRAM_NAME);           
      fputs ("Inicialización del programa servidor.\n\
      -n,   indica el nombre del centro de distribución (cadena de caracteres sin espacios)\n\
      -cp,  capacidad máxima en litros (entero entre 38000 y 3800000)\n\
      -i,   inventario actual (entero entre 0 y capacidad máxima)\n\
      -t,   tiempo de respuesta en minutos (entero entre 0 y 180)\n\
      -s,   suministro promedio en litros por minuto (entero entre 0 y 10000)\n\
      -p,   puerto por el cual escuchará peticiones  (entero entre 1 y 65535)\n", stdout);                           
   }                                                                          
   exit (status);                                                              
}

/* inicializarServidor
 * Descripción: Procedimiento que inicializa la estructura Servidor para evitar
 * que el programa se comporte de manera errónea a causa de valores basura.
 * Parámetro de entrada: 
 * servidorPtr: apuntador a la estructura Servidor
*/
void inicializarServidor(Servidor* servidorPtr){
   servidorPtr->nombreCentro = "";
   servidorPtr->capacidadMaxima = -1;
   servidorPtr->inventario = -1;
   servidorPtr->tiempo = -1;
   servidorPtr->suministro = -1;
   servidorPtr->puerto = -1;
}


/* imprimirServidor
 * Descripción:Procedimiento que imprime en pantalla los valores de la estructura 
 * Servidor.
 * Parámetro de entrada: 
 * servidor: estructura Servidor a ser impresa por pantalla
*/
void imprimirServidor(Servidor servidor){
   printf("\n");
   printf("Estructura Servidor:\n");
   printf("Nombre Centro: %s\n", servidor.nombreCentro);
   printf("Capacidad Máxima: %d\n", servidor.capacidadMaxima);
   printf("Inventario: %d\n", servidor.inventario);
   printf("Tiempo de respuesta: %d\n", servidor.tiempo);
   printf("Suministro promedio: %d\n", servidor.suministro);
   printf("Puerto: %d\n", servidor.puerto);
   printf("\n");
}

int main(int argc, char *argv[]){

   Servidor servidor;
   inicializarServidor(&servidor);
//   imprimirServidor(servidor);
   manejarParametros(argc, argv, &servidor);
   imprimirServidor(servidor);
}
