COMPILER=g++
EXECUTABLE=main a b c d
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

d: d.c
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBRARIES)

e: e.c
	$(COMPILER) $(FLAGS) -o $@ $^ $(LIBRARIES)

clean:
	rm -f *.o $(EXECUTABLE) *~
