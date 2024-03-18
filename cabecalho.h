// cabecalho.h

#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdbool.h>

#define MAX_ESTOQUE 100 // Ajustar conforme a necessidade do estoque

typedef struct {
    char codigo[50];
    char descricao[50];
    int quantidade;
    float preco;
} ItemEstoque;

// Estrutura para uma Pilha
typedef struct {
    ItemEstoque itens[MAX_ESTOQUE];
    int topo;
} PilhaEstoque;

// Estrutura para a fila usada no processamento de itens
typedef struct {
    ItemEstoque itens[MAX_ESTOQUE];
    int inicio;
    int fim;
    int quantidade; // Membro adicionado conforme sugestão
} FilaEstoque;

// Protótipos das funções para manipulação de Pilhas
void inicializarPilha(PilhaEstoque *pilha);
bool pilhaVazia(PilhaEstoque *pilha);
bool pilhaCheia(PilhaEstoque *pilha);
bool empilhar(PilhaEstoque *pilha, ItemEstoque item);
bool desempilhar(PilhaEstoque *pilha, ItemEstoque *item);
void exibirPilhaAdicoes(PilhaEstoque *pilha);
void exibirPilhaRemocoes(PilhaEstoque *pilha);

// Protótipos das funções para manipulação de Filas
void inicializarFila(FilaEstoque *fila);
bool filaVazia(FilaEstoque *fila);
bool filaCheia(FilaEstoque *fila);
bool enfileirar(FilaEstoque *fila, ItemEstoque item);
bool desenfileirar(FilaEstoque *fila, ItemEstoque *item);
void exibirItensFila(FilaEstoque *fila);

// Declarações das funções do sistema de controle de estoque
void limparBuffer();
void clean(const char *opcaoLimpar);
void exibirMensagem(int sucesso, const char *motivo);
bool codigoExiste(ItemEstoque *estoque, int numItens, char *codigo);

void adicionarItem(ItemEstoque** estoque, int* numItens, int* capacidadeEstoque, PilhaEstoque *pilhaAdicoes);
void exibirEstoque(ItemEstoque estoque[], int numItens);
void atualizarInformacoes(ItemEstoque estoque[], int numItens, FilaEstoque *filaProcessamento);
void excluirItem(ItemEstoque estoque[], int *numItens, PilhaEstoque *pilhaRemocoes);
void processarFila(FilaEstoque *fila, ItemEstoque *estoque, int *numItens);
void reverterUltimaOperacao(PilhaEstoque *pilhaAdicoes, PilhaEstoque *pilhaRemocoes, ItemEstoque *estoque, int *numItens);

#endif
