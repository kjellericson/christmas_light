
CC=g++
CFLAGS = -I.
DEPS = main.cpp ledcontrol.cpp ctrl_chase.cpp ctrl_icecrystals.cpp
OBJ = $(DEPS:.cpp=.o)
TARGET = christmas_light

all: $(TARGET)

%.o: %.cpp $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(OBJ)
