
CC=g++
CFLAGS = -I.
DEPS = main.cpp arduino.cpp ledcontrol.cpp ctrl_chase.cpp ctrl_icecrystals.cpp \
	ctrl_traditional.cpp ctrl_redwave.cpp
OBJ = $(DEPS:.cpp=.o)
TARGET = christmas_light

all: $(TARGET)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(OBJ)
