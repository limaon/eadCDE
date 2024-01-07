#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


#define MAX_ESTOQUE 2 // Edite aqui para aumentar a qtd de estoque
#define NUM_CAMPOS 4
#define TIME_SLEEP 3

char codigo[MAX_ESTOQUE][50];
char descricao[MAX_ESTOQUE][50];
int quantidade[MAX_ESTOQUE];
float preco[MAX_ESTOQUE];

int numItens = 0;


// Para quando for apertar o "enter" nao passar direto para o proximo "input"
void limparBuffer() {
    while (getchar() != '\n');
}


// Funcao "clean" para com mais de um uso
void clean(const char *opcaoLimpar) {
    if (strcmp(opcaoLimpar, "aguardeLimpar") == 0) {
        sleep(TIME_SLEEP);
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
        printf("\nOperacao realizada (Aguarde)!\n");
    } else {
        printf("\nFalha na operacao: %s\n", motivo);
    }
    clean("aguardeLimpar");
}


void adicionarItem() {
    if (numItens < MAX_ESTOQUE) {
        printf("Codigo do item: ");
        // scanf("%f", &codigo[numItens]);
        scanf(" %[^\n]s", codigo[numItens]);
        // fgets(codigo, sizeof(codigo), stdin);
        limparBuffer();

        printf("Descricao do item: ");
        scanf(" %[^\n]s", descricao[numItens]);

        printf("Quantidade do item: ");
        scanf("%d", &quantidade[numItens]);

        printf("Preco do item: ");
        scanf("%f", &preco[numItens]);

        numItens++;

        exibirMensagem(1, NULL);

    } else {
        // printf("O estoque esta completo.\n");
        exibirMensagem(0, "O estoque esta completo");
    }
}


void exibirEstoque() {
    // Para verificar se tem itens no array
    if (numItens > 0) {
        printf("Estoque:\n");
        printf("%-10s | %-20s | %-10s | %-10s\n", "Codigo", "Descicao", "Quantidade", "Preco");
        printf("------------------------------------------------------------\n");
        for (int i = 0; i < numItens; i++) {
            printf("%-10s | %-20s | %-10d | %-10.2f\n", codigo[i], descricao[i], quantidade[i], preco[i]);
        }

        printf("\nPressione (Enter) para continuar\n");
        clean("buffer");
        getchar();
    } else {
        printf("Estoque esta vazio (Aguarde).\n");
        clean("aguardeLimpar");
    }
}



void atualizarQuantidade() {
    char codigoItem[50];

    clean("buffer");
    printf("Codigo do item que voce atualizar: ");
    scanf("%[^\n]s", codigoItem);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(codigo[i], codigoItem) == 0) {
            printf("Nova quantidade para o item %s: ", codigoItem);
            scanf("%d", &quantidade[i]);
            printf("\nQuantidade atualizada com sucesso! (Aguarde)\n");
            clean("aguardeLimpar");
            return;
        }
    }

    printf("Item nao encontrado. (Aguarde)\n");
}




void excluirItem() {
    char codigoItem[50];
    clean("buffer");
    printf("Digite o codigo do item que deseja excluir: ");
    scanf("%[^\n]s", codigoItem);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(codigo[i], codigoItem) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                // Dados que serao substituidos por uma capo a frente do array (vazio)
                strcpy(codigo[j], codigo[j + 1]);
                strcpy(descricao[j], descricao[j + 1]);
                quantidade[j] = quantidade[j + 1];
                preco[j] = preco[j + 1];
            }
            numItens--;
            printf("Item excluido com sucesso! (Aguarde)\n");
            clean("aguardeLimpar");
            return;
        }
    }

    printf("Item nao encontrado. (Aguarde)\n");
    clean("aguardeLimpar");
}




int main() {
    int opcao = 0;
    char entrada[10];

    do {
        clean("tela");
        printf("--- | MENU | --- \n");
        printf("1. Adicao de Produtos\n");
        printf("2. Relatorios de Estoque\n");
        printf("3. Atualizacao de Estoque\n");
        printf("4. Excluir Item\n");
        printf("5. Sair\n");
        printf("Opcao: ");
        scanf("%9s", entrada);
        clean("tela");

        // Analizando se o primeiro digito e um numero
        if (!isdigit(entrada[0])) {
            printf("Entrada invalida :( \n");
            sleep(1);
            continue;
        }

        opcao = atoi(entrada); //conveter de char para inteiro

        switch (opcao) {
            case 1:
                printf("Voce escolheu a opcao 1\n");
                adicionarItem();
                break;
            case 2:
                printf("Voce escolheu a opcao 2\n");
                exibirEstoque();
                break;
            case 3:
                printf("Voce escolheu a opcao 3\n");
                atualizarQuantidade();
                break;
            case 4:
                printf("Voce escolheu a opcao 4\n");
                excluirItem();
                break;
            case 5:
                printf("Saindo do programa!!!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente\n");
                break;
        }

    } while (opcao != 5);

    return 0;
}
