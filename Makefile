
CC=g++
CFLAGS = -I.
CL_DEPS = main.cpp arduino.cpp ledcontrol.cpp ctrl_chase.cpp \
	ctrl_traditional.cpp ctrl_redwave.cpp ctrl_twocolorwave.cpp \
	ctrl_icecrystals.cpp
CL_OBJ = $(CL_DEPS:.cpp=.o)
CL_TARGET = christmas_light

CLEAR_TARGET = clear_leds
CLEAR_DEPS = clear_leds.cpp ledcontrol.cpp arduino.cpp
CLEAR_OBJ = $(CLEAR_DEPS:.cpp=.o)

all: $(CL_TARGET) $(CLEAR_TARGET)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(CL_TARGET): $(CL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLEAR_TARGET): $(CLEAR_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(OBJ)
