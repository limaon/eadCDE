#include "cabecalho.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    ItemEstoque* estoque = malloc(MAX_ESTOQUE * sizeof(ItemEstoque));
    
    PilhaEstoque pilhaAdicoes, pilhaRemocoes;
    FilaEstoque filaProcessamento;
    inicializarPilha(&pilhaAdicoes);
    inicializarPilha(&pilhaRemocoes);
    inicializarFila(&filaProcessamento);

    int numItens = 0;
    int capacidadeEstoque = MAX_ESTOQUE;
    int opcao;
    char entrada[10];

    do {
        clean("tela");
        printf("--- | MENU | ---\n");
        printf("1. Adicao de Produtos\n");
        printf("2. Relatorios de Estoque\n");
        printf("3. Atualizacao de Estoque\n");
        printf("4. Excluir Item\n");
        printf("5. Processar proximo item da fila\n");
        printf("6. Reverter ultima operacao\n");
        printf("7. Sair\n");
        printf("Opcao: ");
        scanf("%9s", entrada);
        clean("tela");

        if (!isdigit(entrada[0])) {
            printf("Entrada invalida :(\n");
            continue;
        }

        opcao = atoi(entrada);

        switch (opcao) {
            case 1:
                adicionarItem(&estoque, &numItens, &capacidadeEstoque, &pilhaAdicoes);
                break;
            case 2:
                exibirEstoque(estoque, numItens);
                break;
            case 3:
                atualizarInformacoes(estoque, numItens, &filaProcessamento);
                break;
            case 4:
                excluirItem(estoque, &numItens, &pilhaRemocoes);
                break;
            case 5:
                processarFila(&filaProcessamento, estoque, &numItens);
                break;
            case 6:
                reverterUltimaOperacao(&pilhaAdicoes, &pilhaRemocoes, estoque, &numItens);
                break;
            case 7:
                printf("Obrigado!!!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente\n");
                break;
        }

    } while (opcao != 7);


    if (estoque != NULL) {
        free(estoque); // Libera a memória alocada para o array de estoque
        estoque = NULL; // Define o ponteiro para NULL após liberar a memória
    }

    return 0;
}
