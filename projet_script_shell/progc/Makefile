CC=gcc
CFLAGS=-I.
DEPS = traitements.h tree_avl.h test_avl.h
OBJ = main.o traitements.o tree_avl.o test_avl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)