CC = gcc
CFLAGS = -Wall -Wextra -O2 -I/opt/homebrew/Cellar/mpfr/4.2.1/include -I/opt/homebrew/Cellar/gmp/6.3.0/include
LDFLAGS = -L/opt/homebrew/Cellar/mpfr/4.2.1/lib -L/opt/homebrew/Cellar/gmp/6.3.0/lib -lmpfr -lgmp

SRCS = algo.c mt19937.c
OBJS = $(SRCS:.c=.o)
TARGET = algo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all