// funcoes.c

#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


// Implementacao da Pilha
void inicializarPilha(PilhaEstoque *pilha) {
    pilha->topo = -1;
}

bool pilhaVazia(PilhaEstoque *pilha) {
    return pilha->topo == -1;
}

bool pilhaCheia(PilhaEstoque *pilha) {
    return pilha->topo == MAX_ESTOQUE - 1;
}

bool empilhar(PilhaEstoque *pilha, ItemEstoque item) {
    if (pilhaCheia(pilha)) {
        return false;
    }
    pilha->itens[++pilha->topo] = item;
    return true;
}

bool desempilhar(PilhaEstoque *pilha, ItemEstoque *item) {
    if (pilhaVazia(pilha)) {
        return false;
    }
    *item = pilha->itens[pilha->topo--];
    return true;
}

// Implementacao da Fila
void inicializarFila(FilaEstoque *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

bool filaVazia(FilaEstoque *fila) {
    return fila->quantidade == 0;
}

bool filaCheia(FilaEstoque *fila) {
    return fila->quantidade == MAX_ESTOQUE;
}

bool enfileirar(FilaEstoque *fila, ItemEstoque item) {
    if (filaCheia(fila)) {
        return false;
    }
    fila->itens[fila->fim] = item;
    fila->fim = (fila->fim + 1) % MAX_ESTOQUE;
    fila->quantidade++;
    return true;
}

bool desenfileirar(FilaEstoque *fila, ItemEstoque *item) {
    if (filaVazia(fila)) {
        return false;
    }
    *item = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_ESTOQUE;
    fila->quantidade--;
    return true;
}


// Funcoes úteis
void limparBuffer() {
    while (getchar() != '\n');
}

void clean(const char *opcaoLimpar) {
    if (strcmp(opcaoLimpar, "aguardeLimpar") == 0) {
        limparBuffer();
        getchar();
        system("@cls || clear");
    } else if (strcmp(opcaoLimpar, "tela") == 0) {
        system("@cls || clear");
    } else if (strcmp(opcaoLimpar, "buffer") == 0) {
        limparBuffer();
    } else {
        printf("Opcao de limpeza invalida: %s\n", opcaoLimpar);
    }
}


void exibirMensagem(int sucesso, const char *motivo) {
    if (sucesso) {
        printf("\nOperacao realizada com sucesso!\n");
        printf("Enter para continuar!\n");
    } else {
        printf("\nFalha na operacao: %s\n", motivo);
        printf("Enter para continuar!\n");
    }
    clean("aguardeLimpar");
}


// Implementação da função auxiliar
bool codigoExiste(ItemEstoque *estoque, int numItens, char *codigo) {
    for (int i = 0; i < numItens; i++) {
        if (strcmp(estoque[i].codigo, codigo) == 0) {
            return true; // Código encontrado
        }
    }
    return false; // Código não encontrado
}


// Implementacao das funcoes de CRUD
void adicionarItem(ItemEstoque **estoque, int *numItens, int *capacidadeEstoque, PilhaEstoque *pilhaAdicoes) {

    char codigoTemp[50]; // Buffer temporário para o código
    bool codigoUnico; // Loop para garantir um código único

    if (*numItens >= *capacidadeEstoque) {
        *capacidadeEstoque *= 2;
        *estoque = realloc(*estoque, (*capacidadeEstoque) * sizeof(ItemEstoque));
        if (*estoque == NULL) {
            printf("Erro ao realocar memória.\n");
            exit(EXIT_FAILURE);
        }
    }


    do {
        printf("Código do item: ");
        scanf(" %[^\n]s", codigoTemp);
        limparBuffer();

        codigoUnico = !codigoExiste(*estoque, *numItens, codigoTemp);
        if (!codigoUnico) {
            printf("Código já utilizado. Por favor, insira um código único.\n");
        }
    } while (!codigoUnico);

    // Código confirmado como único, prosseguir com a adição
    strcpy((*estoque)[*numItens].codigo, codigoTemp);


    printf("Descrição do item: ");
    scanf(" %[^\n]s", (*estoque)[*numItens].descricao);

    do {
        printf("Quantidade do item (valor positivo): ");
        scanf("%d", &(*estoque)[*numItens].quantidade);
        limparBuffer();
        if ((*estoque)[*numItens].quantidade <= 0)
            printf("Por favor, insira uma quantidade válida.\n");
    } while ((*estoque)[*numItens].quantidade <= 0);

    do {
        printf("Preço do item (valor positivo): ");
        scanf("%f", &(*estoque)[*numItens].preco);
        limparBuffer();
        if ((*estoque)[*numItens].preco <= 0.0)
            printf("Por favor, insira um preço válido.\n");
    } while ((*estoque)[*numItens].preco <= 0.0);

    empilhar(pilhaAdicoes, (*estoque)[*numItens]);

    (*numItens)++;
    exibirMensagem(1, NULL);
}

void exibirEstoque(ItemEstoque *estoque, int numItens) {
    if (numItens > 0) {
        printf("Estoque:\n");
        printf("%-10s | %-20s | %-10s | %-10s\n", "Codigo", "Descricao", "Quantidade", "Preco");
        printf("------------------------------------------------------------\n");
        for (int i = 0; i < numItens; i++) {
            printf("%-10s | %-20s | %-10d | R$ %-10.2f\n", estoque[i].codigo, estoque[i].descricao, estoque[i].quantidade, estoque[i].preco);
            /* printf("%s - %s - %d - %.2f\n", estoque[i].codigo, estoque[i].descricao, estoque[i].quantidade, estoque[i].preco); */
        }
    } else {
        printf("Estoque está vazio.\n");
    }
    printf("------------------------------------------------------------\n");
    printf("\nEnter para continuar.");
    clean("aguardeLimpar");
}

void atualizarInformacoes(ItemEstoque *estoque, int numItens, FilaEstoque *filaProcessamento) {
    char codigo[50];
    printf("Informe o código do item para atualização: ");
    scanf(" %s", codigo);
    for (int i = 0; i < numItens; i++) {
        if (strcmp(estoque[i].codigo, codigo) == 0) {
            printf("Atualize a descrição: ");
            scanf(" %[^\n]s", estoque[i].descricao);
            printf("Atualize a quantidade: ");
            scanf("%d", &estoque[i].quantidade);
            printf("Atualize o preço: ");
            scanf("%f", &estoque[i].preco);
            enfileirar(filaProcessamento, estoque[i]);
            exibirMensagem(1, "Item atualizado com sucesso.");
            return;
        }
    }
    exibirMensagem(0, "Código não encontrado.");
}

void excluirItem(ItemEstoque *estoque, int *numItens, PilhaEstoque *pilhaRemocoes) {
    char codigo[50];
    printf("Informe o código do item para exclusão: ");
    scanf(" %s", codigo);
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(estoque[i].codigo, codigo) == 0) {
            empilhar(pilhaRemocoes, estoque[i]);
            for (int j = i; j < *numItens - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            (*numItens)--;
            exibirMensagem(1, "Item excluído com sucesso.");
            return;
        }
    }
    exibirMensagem(0, "Código não encontrado.");
}

void processarFila(FilaEstoque *fila, ItemEstoque *estoque, int *numItens) {
    ItemEstoque item;
    if (desenfileirar(fila, &item)) {
        // Processamento do item
        printf("Item processado: %s\n", item.descricao);
    } else {
        printf("Fila vazia.\n");
    }
    exibirMensagem(1, NULL);
}


void reverterUltimaOperacao(PilhaEstoque *pilhaAdicoes, PilhaEstoque *pilhaRemocoes, ItemEstoque *estoque, int *numItens) {
    ItemEstoque item;
    if (!pilhaVazia(pilhaRemocoes)) {
        desempilhar(pilhaRemocoes, &item);
        // Adicionar item de volta ao estoque
    } else if (!pilhaVazia(pilhaAdicoes)) {
        desempilhar(pilhaAdicoes, &item);
        // Remover último item adicionado do estoque
    } else {
        printf("Não há operações para reverter.\n");
    }

    exibirMensagem(1, NULL);
}

void exibirItensFila(FilaEstoque *fila) {
    printf("Itens atualmente na fila de processamento:\n");
    int posicaoAtual = fila->inicio;
    for(int i = 0; i < fila->quantidade; i++) {
        ItemEstoque item = fila->itens[posicaoAtual];
        printf("%d: Código: %s, Descrição: %s, Quantidade: %d, Preço: %.2f\n",
               i+1, item.codigo, item.descricao, item.quantidade, item.preco);
        posicaoAtual = (posicaoAtual + 1) % MAX_ESTOQUE;
    }
    if (fila->quantidade == 0) {
        printf("A fila está vazia.\n");
    }

    exibirMensagem(1, NULL);
}


void exibirPilhaAdicoes(PilhaEstoque *pilha) {
    printf("Últimas adições ao estoque:\n");
    for(int i = pilha->topo; i >= 0; i--) {
        ItemEstoque item = pilha->itens[i];
        printf("%d: Código: %s, Descrição: %s, Quantidade: %d, Preço: %.2f\n",
               pilha->topo - i + 1, item.codigo, item.descricao, item.quantidade, item.preco);
    }
    if (pilha->topo == -1) {
        printf("A pilha de adições está vazia.\n");
    }

    exibirMensagem(1, NULL);
}

void exibirPilhaRemocoes(PilhaEstoque *pilha) {
    printf("Últimas remoções do estoque:\n");
    for(int i = pilha->topo; i >= 0; i--) {
        ItemEstoque item = pilha->itens[i];
        printf("%d: Código: %s, Descrição: %s, Quantidade: %d, Preço: %.2f\n",
               pilha->topo - i + 1, item.codigo, item.descricao, item.quantidade, item.preco);
    }
    if (pilha->topo == -1) {
        printf("A pilha de remoções está vazia.\n");
    }

    exibirMensagem(1, NULL);
}
