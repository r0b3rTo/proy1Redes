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

#include "bomba.h"

/* Funcion obtenerCentros
*    Parametros de entrada: Una lista de Servidores y una estructura de tipo FILE,
*    que apunta a un archivo abierto.
*    Parametro de salida: Una lista de Servidores.
*    Descripción: Toma el apuntador a un file, y lo recorre insertando todos
*    los centros del archivo en la lista.
*/
ListaServidor obtenerCentros(ListaServidor listaCentros, FILE *archivoServidores){
  char servidorInfo [100];
  char* nombreServidor;
  char* direccionServidor;
  int puertoServidor;
  while(fgets(servidorInfo,sizeof(servidorInfo),archivoServidores) != NULL){
      nombreServidor = (char*)malloc(sizeof(char)*100);
      if(nombreServidor == NULL){
         terminar("Error de asignacion de memoria: " );
      }
      direccionServidor = (char*)malloc(sizeof(char)*100);
      if(direccionServidor == NULL){
         terminar("Error de asignacion de memoria: " );
      }
      nombreServidor = strtok(servidorInfo,"&");
      direccionServidor = strtok(NULL,"&");
      puertoServidor = atoi(strtok(NULL,"&\n"));
      listaCentros = insertarServidor(listaCentros,nombreServidor,direccionServidor,puertoServidor,0);
  }
  return listaCentros;
}

/* verificacionNombreBomba
 * Descripción: Procedimiento encargado de la verificación del valor del 
 * modificador -n.
 * En caso de que el valor no sea válido, imprime un mensaje de error.
 * En caso de que el valor sea válido, le coloca un valor TRUE a la variable flagN para 
 * indicar que se inicializó con éxito el parámetro.
 * Parámetros de entrada:
 * nombreBomba: apuntador a la cadena de caracteres que mantiene el valor del
 * nombre de la Bomba.
 * flagN: apuntador a la variable que indica si el valor del parámetro es 
 * correcto.
*/
void verificacionNombreBomba(char** nombreBomba, int *flagN){
   if( strcmp(optarg,"") == 0 ){
      printf("Debe proveer un nombre de Bomba distinto de vacío para el modificador '-n'.\n");
   }else{
      *nombreBomba = optarg;
      *flagN = 1;
   }
}

/* verificacionFicheroCentros
 * Descripción: Procedimiento encargado de la verificación del valor del 
 * modificador -fc.
 * En caso de que el valor no sea válido, imprime un mensaje de error.
 * En caso de que el valor sea válido, le coloca un valor TRUE a la variable flagFC para 
 * indicar que se inicializó con éxito el parámetro.
 * Parámetros de entrada:
 * ficheroCentros: apuntador a la cadena de caracteres que mantiene el valor de
 * la dirección del archivo contenedor de los datos de los centros.
 * flagFC: apuntador a la variable que indica si el valor del parámetro es 
 * correcto.
*/
void verificacionFicheroCentros(char** ficheroCentros, int *flagFC){
   
   if( strcmp(optarg,"") == 0 ){
      printf("Debe proveer una dirección de archivo distinta de vacío para el modificador '-fc'.\n");
   }else{
      FILE *archivo = fopen(optarg,"r");
      if(archivo == NULL){
         printf("El fichero no existe.\n");
      }else{
         fclose(archivo);
         *ficheroCentros = optarg;
         *flagFC = 1;
      }
   }
}


/* verificacionEntero
 * Descripción: Procedimiento encargado de la verificación del valor de
 * los modificadores enteros.
 * En caso de que el valor no sea válido, imprime un mensaje de error.
 * En caso de que el valor sea válido, le coloca un valor TRUE a la variable flagParametro
 * para indicar que se inicializó con éxito el parámetro.
 * Parámetros de entrada:
*/
void verificacionEntero(int opt, int minimo, int maximo, int *variableBomba, int *flagParametro){
   float temp = -1.0;
   sscanf(optarg,"%f",&temp);
   int aux = (int) temp;
   float aux2 = temp-aux;

   if( (aux2 == 0) && (minimo <= temp) && (temp <= maximo) ){
      *variableBomba = temp;
      *flagParametro = 1;
   }else{
      if( (opt == 'i') && (maximo == -1) ){
         //No se ha inicializado el valor del modificador 'cp'-> capacidadMaxima
         printf("El modificador '-i' debe ir precedido por el modificador '-cp' y su valor correspondiente.\n");
      }else if( aux2 != 0 ){
         //Se introdujo un valor flotante
         if( opt == 'm' ){
            printf("El valor del modificador '-cp' debe ser entero.\n");      
         }else{
            printf("El valor del modificador '%c' debe ser entero.\n", opt);
         }
      }else{
         //El valor del parámetro no se encuentra entre el valor de mínimo y máximo
         if( opt == 'm' ){
            printf("Debe proveer un valor para el modificador '-cp' entre %d y %d.\n", minimo, maximo);
         }else{
            printf("Debe proveer un valor para el modificador '-%c' entre %d y %d.\n", opt, minimo, maximo);
         }
      }
   }
}

/* imprimirIndicaciones
 * Descripción: Función que imprime en pantalla la manera apropiada de 
 * invocar el programa.
 * Parámetro de entrada: 
 * estado: entero que indica si el programa termina con éxito o no.
*/
void imprimirIndicaciones(){                                                                                                     
      printf ("Uso: %s -n nombreBomba -cp capacidadMaxima -i inventario -c consumo -fc ficheroCentros\n", PROGRAM_NAME);           
      fputs ("Inicialización del programa bomba.\n\
      -n,   indica el nombre de la bomba (cadena de caracteres sin espacios)\n\
      -cp,  capacidad máxima en litros (entero entre 38000 y 380000)\n\
      -i,   inventario actual (entero entre 0 y capacidad máxima)\n\
      -c,   consumo promedio en litros por minuto (entero entre 0 y 1000)\n\
      -fc,  nombre del archivo que contiene los datos de los centros de distribución\n", stdout);                                                 
}

/* verificarParametrosFaltantes
 * Descripción: Procedimiento que verifica que todos los parámetros de 
 * invocación del programa se hayan inicializado de manera correcta.
 * Parámetros de entrada:
 * flagN
*/
void verificarParametrosFaltantes(int flagN, int flagCP, int flagI, int flagC, int flagFC){
   if(!flagN){
      printf("Falta el modificador '-n' y su valor correspondiente.\n");
   } 
   if(!flagCP){
      printf("Falta el modificador '-cp' y su valor correspondiente.\n");
   } 
   if(!flagI){
      printf("Falta el modificador '-i' y su valor correspondiente.\n");
   } 
   if(!flagC){
      printf("Falta el modificador '-c' y su valor correspondiente.\n");
   }
   if(!flagFC){
      printf("Falta el modificador '-fc' y su valor correspondiente.\n");
   } 
   if(!flagN || !flagCP || !flagI || !flagC || !flagFC){
      imprimirIndicaciones();
      terminar("Error en la invocación del programa: ");
   } 
}


/* manejarParametros
 * Descripción: Procedimiento que maneja apropiadamente los parámetros 
 * introducidos como modificadores a través de la línea de comandos.
 * Parámetros de entrada:
*/
void manejarParametros(int argc, char *argv[], Bomba* bomba){
   int flagN = 0;
   int flagCP = 0;
   int flagI = 0;
   int flagC = 0;
   int flagFC = 0;
   int opt;
   int option_index;
   extern int optopt;
   
   //Lectura de parámetros
   while((opt = getopt_long_only(argc, argv, ":n:i:c:", long_options, &option_index)) != -1){
      switch(opt){
         case 'n':
            verificacionNombreBomba(&bomba->nombreBomba, &flagN);
            break;
         case 'm':
            verificacionEntero(opt, CARGA_GANDOLA, 3800000, &bomba->capacidadMaxima, &flagCP);
            break;
         case 'i':
            verificacionEntero(opt, 0, bomba->capacidadMaxima, &bomba->inventario, &flagI);
            break;
         case 'c':
            verificacionEntero(opt, 1, 1000, &bomba->consumo, &flagC);
            break;
         case 'f':
             verificacionFicheroCentros(&bomba->ficheroCentros, &flagFC);
             break;
         case ':':
            if(optopt == 'm'){
               printf("Falta el valor del modificador '-cp'.\n");
            }else if(optopt == 'f'){
               printf("Falta el valor del modificador '-fc'.\n");
            }else{
               printf("Falta el valor del modificador '-%c'.\n", optopt);
            }
            break;
         case '?':
            printf("Opción desconocida %s\n", argv[optind-1]);
            break;
         default:         
            imprimirIndicaciones();
            terminar("Error en la invocación del programa: ");
      }
   }
   verificarParametrosFaltantes(flagN, flagCP, flagI, flagC, flagFC);
}


/* inicializarBomba
 * Descripción: Procedimiento que inicializa la estructura Bomba para evitar
 * que el programa se comporte de manera errónea a causa de valores basura.
 * Parámetro de entrada: 
 * bomba: apuntador a la estructura Bomba
*/
void inicializarBomba(Bomba* bomba){
   bomba->nombreBomba = "";
   bomba->capacidadMaxima = -1;
   bomba->inventario = -1;
   bomba->consumo = -1;
   bomba->ficheroCentros = "";
}

/* consumirGasolina
 * Descripción: Procedimiento que simula el consumo de gasolina, restándole la tasa
 * al inventario de la Bomba.
 * Parámetro de entrada: 
 * bomba: apuntador a la estructura Bomba.
*/
void consumirGasolina(Bomba* bomba){
   
   if(bomba->inventario < 5*bomba->consumo){
      bomba->inventario = 0;
   }else{
      bomba->inventario = bomba->inventario - 5*bomba->consumo;
   }
}

/* recibirGasolina
 * Descripción: Procedimiento que simula el ingreso de la carga de gasolina.
 * Parámetro de entrada: 
 * bomba: apuntador a la estructura Bomba.
 * 
*/
void recibirGasolina(Bomba* bomba, int nuevaCarga){
   
   bomba->inventario = bomba->inventario + nuevaCarga;
   
}

/* predecirLlamadoCentro
 * Descripción:.
 * Parámetro de entrada: 
 * bomba: apuntador a la estructura Bomba.
 * minutoActual: entero que representa el minuto actual de la simulación.
 * tiempoMinimoRespuesta: entero que representa el tiempo de respuesta mínimo
 * de la lista de Centros.
*/
int predecirLlamadoCentro(Bomba bomba, int minutoActual, int tiempoMinimoRespuesta){
   int t = minutoActual;
   if(bomba.capacidadMaxima - bomba.inventario < CARGA_GANDOLA){
      t = ((CARGA_GANDOLA - (bomba.capacidadMaxima - bomba.inventario)) / bomba.consumo);
      if(t - tiempoMinimoRespuesta >= 0){
         t = t -tiempoMinimoRespuesta;
      }else{
         t = minutoActual;
      }
   }
   return t;
}

/* obtenerTiemposRespuesta
 * Descripción:.
 * Parámetro de entrada: 
 * listaCentros: apuntador a la estructura de tipo ListaServidor que contiene
 * los datos de los distintos centros de distribución.
*/
void obtenerTiemposRespuesta(ListaServidor listaCentros){
   
   int descriptorSocket;
   struct sockaddr_in direccionServidor;
   
   char* mensajeSolicitud = "Solicitud de Tiempo Respuesta";
   char tiempoRespuesta[100];
   int tiempoLeido;
   
   ListaServidor indiceLista = (SERVIDOR*)malloc(sizeof(SERVIDOR)); 
   if(indiceLista == NULL){
      terminar("Error de asignacion de memoria: " );
   }
   indiceLista = listaCentros;
   
   while(indiceLista != NULL){
      /* Obtener la dirección del Centro */
      bzero(&direccionServidor, sizeof(direccionServidor));
      direccionServidor.sin_family = AF_INET;
      direccionServidor.sin_addr.s_addr = inet_addr(indiceLista->direccion);
      direccionServidor.sin_port = htons(indiceLista->puerto);
      printf("Direccion del Centro %s obtenida\n",indiceLista->nombre);
      
      /* Abrir un socket */
      descriptorSocket = socket(AF_INET, SOCK_STREAM, 0);
      if (descriptorSocket < 0){
         errorFatal("Error: No es posible abrir el socket");
      }
      printf("Socket para tiempos de respuesta de Centro %s abierto\n", indiceLista->nombre);
      
      /* Conexión al Centro correspondiente */
      if (connect(descriptorSocket, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor)) < 0){
         mensajeError("Error: No es posible conectarse con el centro\n");
      }else{
         /* Enviar solicitud de Tiempo de Respuesta*/
         if (write(descriptorSocket, mensajeSolicitud, sizeof(mensajeSolicitud)*100) == 0){
            mensajeError("Error: No es posible escribir en el socket\n");
         }

         /* Leer el Tiempo enviado por el Centro correspondiente*/
         if (recv(descriptorSocket, &tiempoRespuesta, sizeof(tiempoRespuesta)*100,0) == 1){
            mensajeError("Error: No es posible recibir información del socket\n");
         }
      }
      printf("Tiempo de Respuesta obtenido: %s\n", tiempoRespuesta);
      if(strcmp(tiempoRespuesta,"") != 0){
         tiempoLeido = atoi(tiempoRespuesta);
         indiceLista->tiempoRespuesta = tiempoLeido;
      }
      
      /* Cerrar el socket*/
      close(descriptorSocket);
      
      indiceLista = indiceLista->siguiente;
   }
   
   printf("obtenerTiemposRespuesta finalizado\n");
}

/* solicitarEnvioGasolina
 * Descripción:.
 * Parámetro de entrada: 
 * listaCentros: apuntador a la estructura de tipo ListaServidor que contiene
 * los datos de los distintos centros de distribución.
 * bomba: apuntador a la estructura Bomba.
 * descriptorSocket: identificador del socket perteneciente a la Bomba.
*/
void solicitarEnvioGasolina(ListaServidor listaCentros, Bomba bomba, int minutoActual, int descriptorSocket){
   
   int solicitudAceptada = 0;
   struct sockaddr_in direccionServidor;
   
   char* mensajeSolicitud = "Solicitud de Gasolina";
   char respuestaSolicitud[100];
   int tiempoEsperaCarga, tiempoEsperaExtra;
   
   ListaServidor copiaListaCentros = (SERVIDOR*)malloc(sizeof(SERVIDOR));
   if(copiaListaCentros == NULL){
      terminar("Error de asignacion de memoria: " );
   }
   copiaListaCentros = listaCentros;
      
   while(copiaListaCentros != NULL){
      /* Obtener la dirección del Centro */
      bzero(&direccionServidor, sizeof(direccionServidor));
      direccionServidor.sin_family = AF_INET;
      direccionServidor.sin_addr.s_addr = inet_addr(INADDR_ANY);
      direccionServidor.sin_port = htons(copiaListaCentros->puerto);
      
      /* Conexión al Centro correspondiente */
      if (connect(descriptorSocket, (struct sockaddr *) &direccionServidor, sizeof(direccionServidor)) < 0){
         mensajeError("Error: No es posible conectarse con el centro\n");
      } else {
         /* Enviar solicitud de Tiempo de Respuesta*/
         if (write(descriptorSocket, mensajeSolicitud, sizeof(mensajeSolicitud)) == 0){
            mensajeError("Error: No es posible escribir en el socket\n");
         }
        
         /* Leer el Tiempo enviado por el Centro correspondiente*/
         if (recv(descriptorSocket, &respuestaSolicitud, sizeof(respuestaSolicitud),0) == 1){
            mensajeError("Error: No es posible recibir información del socket\n");
         }
      }
         
      if(strcmp(respuestaSolicitud,"Ok") == 0){
         printf("Solicitud de Gasolina aceptada por Centro %s\n", copiaListaCentros->nombre);
         solicitudAceptada = 1;
         tiempoEsperaCarga = copiaListaCentros->tiempoRespuesta;
         break;
      }
         
      copiaListaCentros = copiaListaCentros->siguiente;
   }
   
   //Al haber una solicitud aceptada, se espera y se recibe la carga.
   if(solicitudAceptada){
      if(tiempoEsperaCarga > 5){
         tiempoEsperaExtra = tiempoEsperaCarga - 5; 
         usleep(tiempoEsperaExtra*100000);
         minutoActual = minutoActual + tiempoEsperaExtra; 
      }
      recibirGasolina(&bomba,CARGA_GANDOLA);
   }
   
}

int main(int argc, char *argv[]){
   
   Bomba bomba;
   int minuto = 0, minutoSolicitudGasolina;
   FILE *archivoCentros;
   ListaServidor listaCentros = NULL;
   int numeroCentros = 0;
   int tiempoMinimoRespuesta = 0;
   
   int descriptorSocket, numeroPuerto;
   struct sockaddr_in direccionServidor;
   
   inicializarBomba(&bomba);
   manejarParametros(argc, argv, &bomba);
   
   archivoCentros = fopen(bomba.ficheroCentros,"r");
   if(archivoCentros == NULL){
      errorFatal("Error: No se puede accesar al archivo de usuarios\n");
   }
   listaCentros = (SERVIDOR*)malloc(sizeof(SERVIDOR));
   if(listaCentros == NULL){
      terminar("Error de asignacion de memoria: " );
   }
   listaCentros = obtenerCentros(listaCentros, archivoCentros);
   fclose(archivoCentros);
   imprimirServidores(listaCentros);
   printf("Centros obtenidos desde el archivo\n");
   
   obtenerTiemposRespuesta(listaCentros);
   printf("Tiempos de Respuesta obtenidos\n");
   
   ordenarLista(&listaCentros);
   printf("Lista de Centros ordenada\n");
   imprimirServidores(listaCentros);
   tiempoMinimoRespuesta = listaCentros->tiempoRespuesta;
   
   //Creación de socket de la Bomba
   descriptorSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (descriptorSocket < 0){
      errorFatal("Error: No se pudo crear el socket\n");
   }
   
   while(minuto < 480){
      printf("Minuto %d de la simulación. Inventario = %d\n", minuto, bomba.inventario);
      minutoSolicitudGasolina = predecirLlamadoCentro(bomba, minuto, tiempoMinimoRespuesta);
      printf("Minuto de Solicitud a Centros: %d\n", minutoSolicitudGasolina);
      if(minutoSolicitudGasolina <= minuto){
         solicitarEnvioGasolina(listaCentros, bomba, minuto, descriptorSocket);
      }
      usleep(5*100000);
      consumirGasolina(&bomba);
      minuto = minuto + 5;
   }
   
   close(descriptorSocket);
   printf("*** Fin de la simulación ***\n");
   exit(EXIT_SUCCESS);   
}