# Nome do arquivo executável
TARGET = controle_estoque

# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall

# Lista de arquivos fonte
SRCS = main.c funcoes.c

# Lista de arquivos objeto (substitui a extensão .c por .o em SRCS)
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Como construir o alvo final (TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Como construir os arquivos objeto a partir dos arquivos fonte
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Comando para limpar os arquivos compilados, deixando apenas os fontes
clean:
	rm -f $(OBJS) $(TARGET)
