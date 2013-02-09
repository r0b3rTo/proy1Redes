#
#   Definicion de Macros
CC=gcc
CFLAGS = -g
TFLAG = -pthread
#LIBS = -lsocket -lnsl

FUENTES= ListaServidor.o errors.o bomba.o centro.o bomba centro
# El programa esta constituido por 8 archivos:
all : bomba centro

centro: centro.o errors.o ListaServidor.o
	$(CC) -g -pthread centro.o errors.o ListaServidor.o -o centro

bomba: bomba.o errors.o ListaServidor.o
	$(CC) -g bomba.o errors.o ListaServidor.o -o bomba

centro.o: centro.c centro.h ListaServidor.h errors.h
	$(CC) -g -c centro.c 

bomba.o: bomba.c bomba.h ListaServidor.h errors.h
	$(CC) -g -c bomba.c

ListaServidor.o : ListaServidor.c ListaServidor.h
	$(CC) -g -c ListaServidor.c

errors.o : errors.c errors.h
	$(CC) -g -c errors.c

clean:
	rm -f $(FUENTES) *.c~ *.h~ *~
