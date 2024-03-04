// funcoes.c

#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// Implementações das funções aqui
// Por exemplo, a função limparBuffer
void limparBuffer() {
    while (getchar() != '\n');
}

// Implemente as demais funções conforme o código fornecido anteriormente.

// Função "clean" com múltiplos propósitos
void clean(const char *opcaoLimpar) {
    if (strcmp(opcaoLimpar, "aguardeLimpar") == 0) {
        sleep(TIME_SLEEP); // Aguarda um tempo antes de limpar a tela
        system("@cls || clear"); // Limpa a tela no Windows e em sistemas baseados em Unix
    } else if (strcmp(opcaoLimpar, "tela") == 0) {
        system("@cls || clear"); // Limpa a tela imediatamente
    } else if (strcmp(opcaoLimpar, "buffer") == 0) {
        limparBuffer(); // Limpa o buffer de entrada
    } else {
        printf("Opcao de limpeza invalida: %s\n", opcaoLimpar); // Caso a opção não seja reconhecida
    }
}

void exibirMensagem(int sucesso, const char *motivo) {
    if (sucesso) {
        printf("\nOperacao realizada com sucesso!\n");
    } else {
        printf("\nFalha na operacao: %s\n", motivo);
    }
    clean("aguardeLimpar");
}


/*
 * Funcoes relacionadas ao CRUD 
 */

void adicionarItem(ItemEstoque estoque[], int *numItens) {
    if (*numItens >= MAX_ESTOQUE) {
        exibirMensagem(0, "O estoque está completo.");
        return;
    }

    printf("Código do item: ");
    scanf(" %[^\n]s", estoque[*numItens].codigo);
    limparBuffer();

    printf("Descrição do item: ");
    scanf(" %[^\n]s", estoque[*numItens].descricao);

    printf("Quantidade do item: ");
    scanf("%d", &estoque[*numItens].quantidade);

    printf("Preço do item: ");
    scanf("%f", &estoque[*numItens].preco);

    (*numItens)++;
    exibirMensagem(1, NULL);
}


void exibirEstoque(ItemEstoque estoque[], int numItens) {
    if (numItens > 0) {
        printf("Estoque:\n");
        printf("%-10s | %-20s | %-10s | %-10s\n", "Codigo", "Descricao", "Quantidade", "Preco");
        printf("------------------------------------------------------------\n");

        for (int i = 0; i < numItens; i++) {
            printf("%-10s | %-20s | %-10d | R$ %-10.2f\n", estoque[i].codigo, estoque[i].descricao, estoque[i].quantidade, estoque[i].preco);
        }

        printf("\nPressione (Enter) para continuar\n");
        limparBuffer();
        getchar();
    } else {
        printf("Estoque está vazio (Aguarde).\n");
        clean("aguardeLimpar");
    }
}

void atualizarQuantidade(ItemEstoque estoque[], int numItens) {
    char codigoItem[50];
    int novaQuantidade;

    printf("Codigo do item que voce deseja atualizar: ");
    scanf(" %49s", codigoItem); // Le o codigo do item com protecao de buffer
    limparBuffer(); // Limpa o buffer para evitar problemas com a entrada

    for (int i = 0; i < numItens; i++) {
        if (strcmp(estoque[i].codigo, codigoItem) == 0) {
            printf("Nova quantidade para o item %s: ", codigoItem);
            scanf("%d", &novaQuantidade);
            estoque[i].quantidade = novaQuantidade; // Atualiza a quantidade
            printf("\nQuantidade atualizada com sucesso! (Aguarde)\n");
            sleep(TIME_SLEEP); // Espera por alguns segundos
            clean("tela"); // Limpa a tela
            return;
        }
    }

    printf("Item nao encontrado. (Aguarde)\n");
    sleep(TIME_SLEEP); // Espera por alguns segundos antes de limpar a tela
    clean("tela"); // Limpa a tela se o item não for encontrado
}


void excluirItem(ItemEstoque estoque[], int *numItens) {
    char codigoItem[50];
    int i, encontrado = 0;

    printf("Digite o codigo do item que deseja excluir: ");
    scanf("%49s", codigoItem);
    limparBuffer();

    for (i = 0; i < *numItens; i++) {
        if (strcmp(estoque[i].codigo, codigoItem) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        for (int j = i; j < (*numItens) - 1; j++) {
            estoque[j] = estoque[j + 1]; // Desloca os itens subsequentes para "esquerda"
        }
        (*numItens)--; // Decrementa o número total de itens no estoque

        printf("Item excluido com sucesso! (Aguarde)\n");
    } else {
        printf("Item nao encontrado. (Aguarde)\n");
    }

    clean("aguardeLimpar");
}
