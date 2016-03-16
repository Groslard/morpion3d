CC      = gcc
FLAGS  = -L$MESA_PATH/lib -lGL -lGLU -lglut -L/usr/X11R6/lib -lX11
EXEC=$(patsubst %.c, %, $(wildcard *.c))

all: $(EXEC)

$(EXEC):%: %.o
	$(CC) -I$MESA_PATH/include -o $@ $^ $(FLAGS)

%.o: %.c
	$(CC) -o $@ -c $<

##########

.PHONY: clean
clean:
	@rm -rf *.o *~ $(EXEC)
