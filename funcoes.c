// funcoes.c

#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Implementações das funções aqui
// Por exemplo, a função limparBuffer
void limparBuffer() {
    while (getchar() != '\n');
}

// Implemente as demais funções conforme o código fornecido anteriormente.

// Função "clean" com múltiplos propósitos
void clean(const char *opcaoLimpar) {
    if (strcmp(opcaoLimpar, "aguardeLimpar") == 0) {
        limparBuffer();
        getchar();
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
        printf("Enter para continuar!\n");
    } else {
        printf("\nFalha na operacao: %s\n", motivo);
        printf("Enter para continuar!\n");
    }
    clean("aguardeLimpar");
}


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

void atualizarInformacoes(ItemEstoque estoque[], int numItens) {
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
                    scanf("%49[^\n]s", estoque[i].descricao);
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
            exibirMensagem(1, ""); // Assumindo que exibirMensagem foi adaptado para usar sem o segundo argumento quando sucesso.
            return;
        }
    }
    exibirMensagem(0, "Item nao encontrado.");
}


void excluirItem(ItemEstoque estoque[], int *numItens) {
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
            estoque[j] = estoque[j + 1]; // Desloca os itens subsequentes para "esquerda"
        }
        (*numItens)--; // Decrementa o número total de itens no estoque

        printf("Item excluido com sucesso! (Enter)\n");
    } else {
        printf("Item nao encontrado. (Enter)\n");
    }

    clean("aguardeLimpar");
}
