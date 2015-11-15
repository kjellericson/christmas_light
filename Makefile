
CC=g++
CFLAGS=-I.
DEPS = main.c
OBJ = main.o
TARGET = christmas_light

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

