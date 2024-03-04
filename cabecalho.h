// cabecalho.h


#ifndef CABECALHO_H
#define CABECALHO_H

#define MAX_ESTOQUE 2 // Ajustavel conforme a necessidade do estoque
#define TIME_SLEEP 3

typedef struct {
    char codigo[50];
    char descricao[50];
    int quantidade;
    float preco;
} ItemEstoque;

// Declaracoes das funcoes

void limparBuffer();
void clean(const char *opcaoLimpar);
void exibirMensagem(int sucesso, const char *motivo);

// CRUD
void adicionarItem(ItemEstoque estoque[], int *numItens);
void exibirEstoque(ItemEstoque estoque[], int numItens);
void atualizarQuantidade(ItemEstoque estoque[], int numItens);
void excluirItem(ItemEstoque estoque[], int *numItens);

#endif
