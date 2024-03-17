// funcoes.c

#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void adicionarItem(ItemEstoque **estoque, int *numItens, int *capacidadeEstoque) {
    if (*numItens >= *capacidadeEstoque) {
        *capacidadeEstoque *= 2;
        *estoque = realloc(*estoque, (*capacidadeEstoque) * sizeof(ItemEstoque));
        if (*estoque == NULL) {
            printf("Erro ao realocar memória.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Código do item: ");
    scanf(" %[^\n]s", (*estoque)[*numItens].codigo);
    limparBuffer();

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
        }

        printf("\nPressione (Enter) para continuar\n");
        limparBuffer();
        getchar();
    } else {
        printf("Estoque está vazio (Aguarde).\n");
        clean("aguardeLimpar");
    }
}

void atualizarInformacoes(ItemEstoque *estoque, int numItens) {
    char codigoItem[50];
    int opcao;

    printf("Codigo do item que deseja atualizar: ");
    scanf("%49s", codigoItem);
    limparBuffer();

    for (int i = 0; i < numItens; i++) {
        if (strcmp(estoque[i].codigo, codigoItem) == 0) {
            printf("Qual informacao voce deseja editar?\n");
            printf("1. Descricao\n");
            printf("2. Quantidade\n");
            printf("3. Preco\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            limparBuffer();

            switch (opcao) {
                case 1:
                    printf("Nova descricao para o item %s: ", codigoItem);
                    scanf(" %[^\n]s", estoque[i].descricao);
                    break;
                case 2:
                    printf("Nova quantidade para o item %s: ", codigoItem);
                    scanf("%d", &estoque[i].quantidade);
                    break;
                case 3:
                    printf("Novo preco para o item %s: ", codigoItem);
                    scanf("%f", &estoque[i].preco);
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }
            exibirMensagem(1, "");
            return;
        }
    }
    exibirMensagem(0, "Item nao encontrado.");
}

void excluirItem(ItemEstoque *estoque, int *numItens) {
    char codigoItem[50];
    int i, encontrado = 0;

    printf("Digite o codigo do item que deseja excluir: ");
    scanf("%49s", codigoItem);

    for (i = 0; i < *numItens; i++) {
        if (strcmp(estoque[i].codigo, codigoItem) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        for (int j = i; j < (*numItens) - 1; j++) {
            estoque[j] = estoque[j + 1];
        }
        (*numItens)--;
        printf("Item excluido com sucesso! (Enter)\n");
    } else {
        printf("Item nao encontrado. (Enter)\n");
    }

    clean("aguardeLimpar");
}
