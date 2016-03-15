CC      = gcc
CFLAGS  = -Wall $(shell sdl-config --cflags)
LDFLAGS = $(shell sdl-config --libs)
EXEC=$(patsubst %.c, %, $(wildcard exercice*.c))

all: $(EXEC)

$(EXEC):%: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

########## 

.PHONY: clean
clean:
	@rm -rf *.o *~ $(EXEC)