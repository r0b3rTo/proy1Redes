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
      // Caso en que se indica como nombre la cadena de caracteres vacía.
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
 * opt: se refiere al caracter que indica cuál modificador se está verificando.
 * minimo: valor mínimo que puede aceptar el modificador como parámetro.
 * maximo: valor máximo que puede aceptar el modificador como parámetro.
 * variableServidor: apuntador a la variable que almacena en la estructura Servidor
 * el valor dado al modificador en caso de que el valor sea válido.
 * flagParametro: apuntador a la variable que indica si el flag se inicializó 
 * de manera correcta o no.
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
 * invocación del programa se hayan inicializado de manera correcta. En caso
 * contrario, imprime por pantalla el error que fue detectado e invoca al
 * procedimiento usage que imprime la manera correcta de invocar al programa.
 * Parámetros de entrada:
 * flagN, flagC, flagI, flagT, flagS, flagP: valores enteros que indican si
 * el modificador al que corresponden fue inicializado de manera correcta.
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
 * argc: entero que indica el tamaño del arreglo argv[]
 * argv: arreglo de caracteres que contiene las opciones pasadas al programa a 
 * través de la línea de comandos.
 * servidor: apuntador a la estructura Servidor donde se guardarán los valores
 * pasados a los modificadores en caso de que sean válidos.
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
 * servidorPtr: apuntador a la estructura Servidor.
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
 * Descripción: Procedimiento que imprime en pantalla los valores de la estructura 
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


/* obtenerNombreArchivoLog
 * Descripción: Función que retorna el nombre del archivo bitácora de la
 * ejecución del servidor, a partir del nombre del Centro de Distribución.
 * Parámetro de entrada:
 * nombreCentro: apuntador a una cadena de caracteres que representa el nombre 
 * del Centro de Distribución.
*/
char * obtenerNombreArchivoLog(char * nombreCentro){
   char* nombreArchivo = (char*)malloc(sizeof(char)*100);
   if(nombreArchivo == NULL){
      terminar("Error de asignacion de memoria");
   }
   strcpy(nombreArchivo,"log_");
   strcat(nombreArchivo,nombreCentro); 
   strcat(nombreArchivo,".txt");
   return nombreArchivo;
}


/* crearLog
 * Descripción: Procedimiento que crea el archivo bitácora de ejecución del 
 * servidor. En caso de que ya haya un archivo creado con el mismo nombre 
 * correspondiente, lo sobreescribe.
 * Parámetro de entrada:
 * nombreServidor: Apuntador a la cadena de caracteres dentro de la estructura 
 * Servidor que guarda el nombre del Centro de Distribución.
*/
void crearLog(char * nombreCentro){
   char * nombreArchivoLog = obtenerNombreArchivoLog(nombreCentro);
   FILE *archivoLog;
   archivoLog = fopen(nombreArchivoLog,"w+");
   if(archivoLog == NULL){
      mensajeError("Error: No se puede accesar al archivo del log del Centro de Distribución.\n");
   }

}


/* escribirArchivoLog
 * Descripción: Procedimiento que se encarga de actualizar el archivo bitácora 
 * de la ejecución del servidor. 
 * Parámetros de entrada:
 * nombreArchivoLog: apuntador a una cadena de caracteres que representa el 
 * nombre del archivo bitácora de ejecución del servidor.
 * mensaje: apuntador a una cadena de caracteres que indica el tipo de mensaje
 * que se debe añadir a la bitácora del servidor, de acuerdo al evento 
 * relevante ocurrido durante la simulación.
 * tiempoActual: valor entero que indica el momento de la simulación en que 
 * ocurre el evento relevante.
 * inventario: valor entero que indica el nivel del inventario del Centro de 
 * Distribución al momento de ocurrir el evento relevante.
 * nombreBomba: nombre de la bomba o estación de servicio que se está 
 * comunicando con el servidor.
 * resultadoPeticion: resultado de la petición solicitada por el programa 
 * cliente.
*/
void escribirArchivoLog(char* nombreArchivoLog, char* mensaje, int tiempoActual, int inventario,
   char* nombreBomba, char* resultadoPeticion){
   char bufferTiempo[100];
   char bufferInventario[100];   
   
   FILE *archivoLog;
   archivoLog = fopen(nombreArchivoLog,"a");
   if(archivoLog == NULL){
      mensajeError("Error: No se puede accesar al archivo del log del Centro de Distribución.\n");
   }
   
   char* nuevaEntrada = (char*)malloc(sizeof(char)*256);
   if(nuevaEntrada == NULL){
      terminar("Error de asignacion de memoria: " );
   }
   
   strcpy(nuevaEntrada, mensaje);
   strcat(nuevaEntrada, ": ");
   if(strcmp(mensaje,"Estado Inicial") == 0){
      sprintf(bufferInventario,"%d", inventario);
      strcat(nuevaEntrada, bufferInventario);
      strcat(nuevaEntrada, " litros");
   }else if(strcmp(mensaje, "Tanque full") == 0){
      strcat(nuevaEntrada, "Minuto ");
      sprintf(bufferTiempo,"%d",tiempoActual);
      strcat(nuevaEntrada, bufferTiempo);
   }else if(strcmp(mensaje, "Tanque vacio") == 0){
      strcat(nuevaEntrada, "Minuto ");
      sprintf(bufferTiempo,"%d",tiempoActual);
      strcat(nuevaEntrada, bufferTiempo);
   }else if(strcmp(mensaje, "Suministro") == 0){
      strcat(nuevaEntrada, "Minuto ");
      sprintf(bufferTiempo,"%d",tiempoActual);
      strcat(nuevaEntrada, bufferTiempo);
      strcat(nuevaEntrada, ", ");
      strcat(nuevaEntrada, nombreBomba);
      strcat(nuevaEntrada, ", ");
      strcat(nuevaEntrada, resultadoPeticion);
      strcat(nuevaEntrada, ", ");
      sprintf(bufferInventario, "%d", inventario);
      strcat(nuevaEntrada, bufferInventario);
   }
   strcat(nuevaEntrada,"\n");
      
   if(fwrite(nuevaEntrada, sizeof(char), strlen(nuevaEntrada), archivoLog) < strlen(nuevaEntrada)){
      mensajeError("Error: No se pudo escribir correctamente en el archivo bitácora del Centro de Distribución.\n");
   }   
   fclose(archivoLog);
}

/* atenderSolicitud
 * Descripción: Función que ejecuta el hilo encargado de atender una solicitud
 * de un cliente conectado.
 * Parámetros de entrada:
 * argumento: apuntador a una estructura Parametros que contiene a su vez un 
 * apuntador a la estructura Servidor y un apuntador al descriptor de archivo
 * devuelto por la función accept.
*/
void * atenderSolicitud(void * argumento){
   Parametros * parametros = (Parametros *) (argumento);
   char mensajeDelCliente[256];
   char tiempo[100];
   char* solicitudGasolina = (char*)malloc(sizeof(char)*256);
   if(solicitudGasolina == NULL){
      terminar("Error de asignacion de memoria" );
   }
   char* nombreBomba = (char*)malloc(sizeof(char)*256);
   if(nombreBomba == NULL){
      terminar("Error de asignacion de memoria" );
   }
   char* mensajeOk = "Ok";
   char* mensajeNoDisponible = "No disponible";
   char* nombreArchivoLog = obtenerNombreArchivoLog(parametros->servidor->nombreCentro);
   
   bzero(mensajeDelCliente,256);
   if( read(*parametros->descriptorSocket, &mensajeDelCliente, 256) > 0 ){
      if( strcmp(mensajeDelCliente,"Solicitud de Tiempo Respuesta") == 0){
         pthread_mutex_lock(&mutex_tiempoRespuesta);
         sprintf(tiempo, "%d", parametros->servidor->tiempo);
         pthread_mutex_unlock(&mutex_tiempoRespuesta);
         write(*parametros->descriptorSocket, tiempo, 100);
      } else {
         nombreBomba = strtok(mensajeDelCliente,"&");
         solicitudGasolina = strtok(NULL,"\n");
         if ( strcmp(solicitudGasolina,"Solicitud de Gasolina") == 0 ){
            pthread_mutex_lock(&mutex_inventario);
            if(parametros->servidor->inventario >= 38000){
               write(*parametros->descriptorSocket, mensajeOk, strlen(mensajeOk));
               parametros->servidor->inventario = parametros->servidor->inventario - 38000;
               escribirArchivoLog(nombreArchivoLog, "Suministro", parametros->servidor->tiempoSimulacion, 
                                    parametros->servidor->inventario, nombreBomba, mensajeOk);
            }else{
               write(*parametros->descriptorSocket, mensajeNoDisponible, strlen(mensajeNoDisponible));
               escribirArchivoLog(nombreArchivoLog, "Suministro", parametros->servidor->tiempoSimulacion, 
                                    parametros->servidor->inventario, nombreBomba, mensajeNoDisponible);
            }
            pthread_mutex_unlock(&mutex_inventario);
         }
      }
   }
}


/* manejarConexiones
 * Descripción: Función que ejecuta el hilo encargado de manejar las 
 * conexiones de los clientes.
 * Parámetro de entrada: Un apuntador sin tipo a una variable de tipo
 * Servidor
*/
void * manejarConexiones(void * argumento){
   Servidor * servidor = (Servidor *) (argumento);
   pthread_t hiloTrabajador;
   int descriptorSocket, descriptorSocketCliente;    //Se declaran los descriptores de archivo de los sockets
   struct sockaddr_in direccionCliente, direccionServidor;  
   int tamanioDireccionCliente;
   
   Parametros parametros;
   parametros.servidor = servidor;
   parametros.descriptorSocket = &descriptorSocketCliente;
   
   // Se crea el socket
   descriptorSocket = socket(AF_INET, SOCK_STREAM, 0);
   if( descriptorSocket < 0){
      errorFatal("No fue posible crear el socket.");
   }
   
   // Se asigna un puerto al socket
   bzero(&direccionServidor, sizeof(direccionServidor));
   direccionServidor.sin_family = AF_INET;
   direccionServidor.sin_addr.s_addr = htonl(INADDR_ANY);
   direccionServidor.sin_port = htons(servidor->puerto);
   if (bind(descriptorSocket, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor)) != 0){
      errorFatal("No se pudo hacer bind al socket.");
   }
   
   // Se establece el número máximo de clientes en espera
   if (listen(descriptorSocket, TAMANIO_COLA) < 0){
      errorFatal("El socket no puede escuchar.");
   }

   while(servidor->tiempoSimulacion < TIEMPO_SIMULACION){ 
      // Se aceptan las conexiones de los clientes
      tamanioDireccionCliente = sizeof(direccionCliente);
      descriptorSocketCliente = accept(descriptorSocket, (struct sockaddr *) &direccionCliente, &tamanioDireccionCliente);
      if (descriptorSocketCliente < 0) {
         errorFatal("Falla en el accept.");         
      }

      // Crea el hilo que se encargará de atender la solicitud del cliente
      if (pthread_create(&hiloTrabajador,NULL,atenderSolicitud,(void *)&parametros) != 0) {
         fprintf(stderr,"No se pudo crear el thread hilo:%s\n",strerror(errno));
      }
   
      //HLM 
      if (pthread_join(hiloTrabajador,NULL) != 0 ){
         fprintf(stderr,"Hubo un problema con la terminación del hilo Trabajador: %s\n",strerror(errno));
      }//HLM 

      close(descriptorSocketCliente);
   } 
   
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
   
   char * nombreArchivoLog = obtenerNombreArchivoLog(servidor->nombreCentro);
   escribirArchivoLog(nombreArchivoLog, "Estado Inicial", 0, servidor->inventario, servidor->nombreCentro, "");

   while(servidor->tiempoSimulacion < TIEMPO_SIMULACION){
      printf("Minuto %d de la simulación. Inventario = %d\n", servidor->tiempoSimulacion, servidor->inventario);
      usleep(50*10000); //HLM hay que cambiar a 100*1000
      pthread_mutex_lock(&mutex_inventario);
      if(servidor->inventario == 0){
         // Tanque vacío
         escribirArchivoLog(nombreArchivoLog, "Tanque vacio", servidor->tiempoSimulacion, servidor->inventario, servidor->nombreCentro,"");
      }else if(servidor->inventario == servidor->capacidadMaxima){
         // Tanque full
         escribirArchivoLog(nombreArchivoLog, "Tanque full" , servidor->tiempoSimulacion, servidor->inventario, servidor->nombreCentro, "");
      }
      if( servidor->capacidadMaxima >= (servidor->inventario + servidor->suministro)){
         servidor->inventario = servidor->inventario + servidor->suministro;
      }
      pthread_mutex_unlock(&mutex_inventario);
      servidor->tiempoSimulacion = servidor->tiempoSimulacion + 1;
   }
   printf("*** Fin de la simulación ***\n");

   // Se conecta al puerto del servidor para desbloquear al hiloManejador
   // Se inicializa la estructura con la dirección del servidor
   bzero(&direccionServidor, sizeof(direccionServidor));
   direccionServidor.sin_family = AF_INET;
   direccionServidor.sin_addr.s_addr = inet_addr(ipServidor);
   direccionServidor.sin_port = htons(servidor->puerto);
   // Se crea el socket
   descriptorSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (descriptorSocket < 0)
      errorFatal("No fue posible crear el socket.\n");
   // Se hace la conexión al socket
   if (connect(descriptorSocket, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor)) < 0)
      errorFatal("No se pudo realizar la conexión al socket.\n");

   // Se cierra el descriptor del socket.
    close(descriptorSocket);

   //Termina
   pthread_exit(0);
}



int main(int argc, char *argv[]){
   Servidor servidor;
   pthread_t hiloActualizador, hiloManejador;
   
   inicializarServidor(&servidor);
// imprimirServidor(servidor);   HLM Este flag no es necesario...
   manejarParametros(argc, argv, &servidor);
//   imprimirServidor(servidor); //HLM Este flag no es necesario...
   crearLog(servidor.nombreCentro);
   pthread_mutex_init(&mutex_inventario, NULL);
   pthread_mutex_init(&mutex_tiempoRespuesta, NULL);
        
   // Crea el hilo que se encargara de manejar la conexiones de los clientes.
   if (pthread_create(&hiloManejador,NULL,manejarConexiones,(void *)&servidor) != 0) {
      fprintf(stderr,"No se pudo crear el thread hilo Manejador: %s\n",strerror(errno));
   }
  
   // Crea el hilo que se encargara de actualizar los valores de la simulación.
   if (pthread_create(&hiloActualizador,NULL,actualizarSimulacion,(void *)&servidor) != 0) {
      fprintf(stderr,"No se pudo crear el thread hilo Actualizador: %s\n",strerror(errno));
   }

   // Espera a que el hilo que actualiza los valores de la simulación termine.
   if (pthread_join(hiloActualizador,NULL) != 0 ){
      fprintf(stderr,"Hubo un problema con la terminación del hilo Actualizador: %s\n",strerror(errno));
   }

   //Espera a que el hilo que maneja las conexiones de los clientes termine.
   if (pthread_join(hiloManejador,NULL) != 0 ){
      fprintf(stderr,"Hubo un problema con la terminación del hilo Manejador: %s\n",strerror(errno));
   }

   pthread_mutex_destroy(&mutex_inventario);   
   pthread_mutex_destroy(&mutex_tiempoRespuesta);   
   printf("El programa principal ha terminado con éxito.\n"); //HLM Este flag no es necesario...
   imprimirServidor(servidor); //HLM Este flag no es necesario...

   return 0;
}
