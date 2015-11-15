
CC=g++
CFLAGS=-I.
DEPS = main.c ledcontrol.c ctrl_chase.c
OBJ = $(DEPS:.c=.o)
TARGET = christmas_light

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

