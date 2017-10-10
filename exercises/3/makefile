COMPILER=gcc
EXECUTABLE=main
FLAGS=-Wall -g
LIBRARIES=-lm -lGL -lGLU -lglut
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBRARIES)

%.o: %.c $(HEADERS)
	$(COMPILER) $(FLAGS) -c $<

clean:
	rm -f *.o $(EXECUTABLE) *~
