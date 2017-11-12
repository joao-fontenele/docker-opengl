COMPILER=g++
EXECUTABLE=main a b
FLAGS=-Wall -g
LIBRARIES=-lm -lGL -lGLU -lglut
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(EXECUTABLE)

main: main.c
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBRARIES)

a: a.c
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBRARIES)

b: b.c
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBRARIES)

c: c.c
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBRARIES)

clean:
	rm -f *.o $(EXECUTABLE) *~
