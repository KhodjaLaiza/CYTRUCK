CC=gcc
CFLAGS=-I.
DEPS = traitements.h
OBJ = main.o traitements.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)