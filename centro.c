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


void die(char *message) {
     perror(message);
       exit(1);
}

void copyData(int from, int to) {
   char buf[1024];
   int amount;

   while ((amount = read(from, buf, sizeof(buf))) > 0){
      if (write(to, buf, amount) != amount) {
         die("write");
         return;
      }
   }
   if (amount < 0) die("read");
}


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
      printf("\n");
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
   servidorPtr->tiempoSimulacion = 0;
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


/* manejarConexiones
 * Descripción: Función que ejecuta el hilo encargado de manejar las 
 * conexiones de los clientes.
 * Parámetro de entrada:
*/
void * manejarConexiones(void * argumento){
   Servidor * servidor = (Servidor *) (argumento);
   printf("Comienzo a manejar las conexiones.\n");   
   printf("El valor del puerto del servidor es %d.\n", servidor->puerto);   
   
   int descriptorSocket, descriptorSocketCliente;    //Se declaran los descriptores de archivo de los sockets
   struct sockaddr_in direccionCliente, direccionServidor;  
   int tamanioDireccionCliente;
   
   //Se crea el socket
   descriptorSocket = socket(AF_INET, SOCK_STREAM, 0);
   if( descriptorSocket < 0){
      errorFatal("No fue posible crear el socket.");
   }
   
   //Se asigna un puerto al socket
   bzero(&direccionServidor, sizeof(direccionServidor));
   direccionServidor.sin_family = AF_INET;
   direccionServidor.sin_addr.s_addr = htonl(INADDR_ANY);
   direccionServidor.sin_port = htons(servidor->puerto);
   if (bind(descriptorSocket, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor)) != 0){
      errorFatal("No se pudo hacer bind al socket.");
   }
   
   //Se pone a escuchar al socket
   if (listen(descriptorSocket, TAMANIO_COLA) < 0){
      errorFatal("El socket no puede escuchar.");
   }

   while(servidor->tiempoSimulacion < TIEMPO_SIMULACION){ 
      //Se aceptan las conexiones
      tamanioDireccionCliente = sizeof(direccionCliente);
      descriptorSocketCliente = accept(descriptorSocket, (struct sockaddr *) &direccionCliente, &tamanioDireccionCliente);
      if (descriptorSocketCliente < 0) {
         errorFatal("Falla en el accept.");         
      }
//      if(servidor->tiempoSimulacion < TIEMPO_SIMULACION){
//         break;
//      }
      /*   printf("...getting data\n");
         copyData(descriptorSocketCliente,1);
         printf("...Done\n");
         close(descriptorSocketCliente);
         */
      
//      close(descriptorSocketCliente);
   } 

   close(descriptorSocketCliente);
   
   printf("Termino de manejar las conexiones.\n");
   pthread_exit(&(servidor->puerto));
}


/* actualizarSimulación
 * Descripción: Función que ejecuta el hilo encargado de controlar el tiempo 
 * de ejecución del servidor y actualiza el valor del inventario de acuerdo al
 * valor indicado para el modificador suministro (-s).
 * Parámetro de entrada:
*/
void * actualizarSimulacion(void *argumento){
   Servidor * servidor = (Servidor *) (argumento);
   int descriptorSocket;
   struct sockaddr_in direccionServidor;
   char * ipServidor;
   ipServidor = "127.0.0.1";


   while(servidor->tiempoSimulacion < TIEMPO_SIMULACION){
      printf("Minuto %d de la simulación. Inventario = %d\n", servidor->tiempoSimulacion, servidor->inventario);
      usleep(50*1000);
      if( servidor->capacidadMaxima >= (servidor->inventario + servidor->suministro)){
         servidor->inventario = servidor->inventario + servidor->suministro;
      }
       servidor->tiempoSimulacion = servidor->tiempoSimulacion + 1;
   }
   printf("*** Fin de la simulación ***\n");

   //Se conecta al puerto del servidor para desbloquear al hiloManejador
   /* Get the address of the server. */
   bzero(&direccionServidor, sizeof(direccionServidor));
   direccionServidor.sin_family = AF_INET;
   direccionServidor.sin_addr.s_addr = inet_addr(ipServidor);
   direccionServidor.sin_port = htons(servidor->puerto);

   /* Open a socket. */
   descriptorSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (descriptorSocket < 0)
      errorFatal("can't open socket");
   /* Connect to the server. */
   if (connect(descriptorSocket, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor)) < 0)
      errorFatal("can't connect to server");

   /* Copy input to the server. */
    close(descriptorSocket);

   //Termina
   pthread_exit(0);
}



int main(int argc, char *argv[]){
   pthread_t hiloActualizador, hiloManejador;
   int * retorna;
   Servidor servidor;
   
   inicializarServidor(&servidor);
// imprimirServidor(servidor);   HLM Este flag no es necesario...
   manejarParametros(argc, argv, &servidor);
   imprimirServidor(servidor); //HLM Este flag no es necesario...
        
   //Crea el hilo que se encargara de manejar la conexiones de los clientes.
   if (pthread_create(&hiloManejador,NULL,manejarConexiones,(void *)&servidor) != 0) {
      fprintf(stderr,"No se pudo crear el thread hilo:%s\n",strerror(errno));
   }
  
   //Crea el hilo que se encargara de acutalizar los valores de la simulación.
   if (pthread_create(&hiloActualizador,NULL,actualizarSimulacion,(void *)&servidor) != 0) {
      fprintf(stderr,"No se pudo crear el thread hilo:%s\n",strerror(errno));
   }

  
   //Espera a que el hilo que actualiza los valores de la simulación termine.
   if (pthread_join(hiloActualizador,NULL) != 0 ){
      fprintf(stderr,"Hubo un problema con la terminación del hilo Junior: %s\n",strerror(errno));
   }

   //Espera a que el hilo que maneja las conexiones de los clientes termine.
   if (pthread_join(hiloManejador,(void**)&retorna) != 0 ){
      fprintf(stderr,"Hubo un problema con la terminación del hilo Junior: %s\n",strerror(errno));
   }
   printf("El hilo manejador retorna %d\n", *retorna);
   
   printf("La simulación ha terminado con éxito.\n"); //HLM Este flag no es necesario...
   imprimirServidor(servidor); //HLM Este flag no es necesario...

   return 0;
}
