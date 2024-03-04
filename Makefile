CC=gcc
CFLAGS=-I.
DEPS = cabecalho.h
OBJ = funcoes.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

estoque: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o estoque
