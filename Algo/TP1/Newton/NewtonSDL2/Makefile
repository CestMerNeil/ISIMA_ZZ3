# Makefile pour les applications SDL2 sur Mac

#CC = /usr/local/Cellar/gcc/9.2.0_3/bin/gcc-9
CC = gcc
CFLAGS  = -Wall -Wextra

CFLAGSGRAPH  = -I/usr/local/include
LDFLAGSGRAPH = -L/usr/local/lib 
LDLIBS = -lSDL2 

SRC1 = newtonSDL2.c complexe.c fonctions.c
OBJ1 = $(SRC1:.c=.o)

newtonSDL2 : $(OBJ1)
	$(CC)  $(LDFLAGSGRAPH) -o $@ $(OBJ1) $(LDLIBS)

%.o : %.c 
	$(CC) $(CFLAGS) $(CFLAGSGRAPH) -c $< -o $@

clean:	
	\rm  newtonSDL2 $(OBJ1)

