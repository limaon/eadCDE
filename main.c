// main.c

#include "cabecalho.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    ItemEstoque estoque[MAX_ESTOQUE];
    int numItens = 0;
    int opcao;
    char entrada[10];

    do {
        clean("tela");
        printf("--- | MENU | ---\n");
        printf("1. Adicao de Produtos\n");
        printf("2. Relatorios de Estoque\n");
        printf("3. Atualizacao de Estoque\n");
        printf("4. Excluir Item\n");
        printf("5. Sair\n");
        printf("Opcao: ");
        scanf("%9s", entrada);
        clean("tela");

        // Verificar se a entrada é um dígito
        if (!isdigit(entrada[0])) {
            printf("Entrada invalida :(\n");
            // sleep(1);
            continue;
        }

        opcao = atoi(entrada); // Converter de char para inteiro

        switch (opcao) {
            case 1:
                printf("Voce escolheu a opcao 1\n");
                adicionarItem(estoque, &numItens);
                break;
            case 2:
                printf("Voce escolheu a opcao 2\n");
                exibirEstoque(estoque, numItens);
                break;
            case 3:
                printf("Voce escolheu a opcao 3\n");
                atualizarInformacoes(estoque, numItens);
                break;
            case 4:
                printf("Voce escolheu a opcao 4\n");
                excluirItem(estoque, &numItens);
                break;
            case 5:
                printf("Obrigado!!!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente\n");
                break;
        }

    } while (opcao != 5);

    return 0;
}
