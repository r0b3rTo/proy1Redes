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
	$(CC) -pthread centro.o errors.o ListaServidor.o -o centro

bomba: bomba.o errors.o ListaServidor.o
	$(CC) bomba.o errors.o ListaServidor.o -o bomba

centro.o: centro.c centro.h ListaServidor.h errors.h
	$(CC) -c centro.c 

bomba.o: bomba.c bomba.h ListaServidor.h errors.h
	$(CC) -c bomba.c

ListaServidor.o : ListaServidor.c ListaServidor.h
	$(CC) -c ListaServidor.c

errors.o : errors.c errors.h
	$(CC) -c errors.c

clean:
	rm -f $(FUENTES) *.c~ *.h~ *~
