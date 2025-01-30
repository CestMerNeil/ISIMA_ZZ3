# Makefile pour les applications X

CC = gcc 
CFLAGS = -I/usr/X11/include -Wall -ansi -pedantic
LDFLAGS = -L/usr/X11/lib
LDLIBS = -lX11

SRC1 = newton31012014.c complexe.c fonctions.c
OBJ1 = $(SRC1:.c=.o)

newton : $(OBJ1)
	$(CC) $(LDLAGS) -o $@ $(OBJ1) $(LDLIBS)

%.o : %.c 
	$(CC) $(CFLAGS) -c $<

clean:	
	\rm  newton *.o

