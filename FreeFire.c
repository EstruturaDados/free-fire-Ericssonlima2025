#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// -----------------------------------------------------------------------------
// Struct que representa um item da mochila
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// -----------------------------------------------------------------------------
// Funções do sistema
// -----------------------------------------------------------------------------
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

// -----------------------------------------------------------------------------
// Função principal
// -----------------------------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int total = 0; // quantidade atual de itens cadastrados
    int opcao;

    do {
        printf("\n========== MOCHILA DO JOGADOR ==========\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// -----------------------------------------------------------------------------
// Inserir novo item na mochila
// -----------------------------------------------------------------------------
void inserirItem(Item mochila[], int *total) {

    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! Remova algum item antes.\n");
        return;
    }

    Item novo;
    printf("\nNome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo do item (arma, municao, cura...): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;

    printf("\nItem cadastrado com sucesso!\n");
    listarItens(mochila, *total);
}

// -----------------------------------------------------------------------------
// Remover item da mochila pelo nome
// -----------------------------------------------------------------------------
void removerItem(Item mochila[], int *total) {
    char nome[30];
    int i, j;

    if (*total == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\nDigite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {

            for (j = i; j < (*total) - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;
            printf("\nItem removido com sucesso!\n");
            listarItens(mochila, *total);
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}

// -----------------------------------------------------------------------------
// Listar todos os itens cadastrados
// -----------------------------------------------------------------------------
void listarItens(Item mochila[], int total) {
    int i;

    printf("\n========== ITENS NA MOCHILA ==========\n");

    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
            i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// -----------------------------------------------------------------------------
// Buscar item pelo nome (busca sequencial)
// -----------------------------------------------------------------------------
void buscarItem(Item mochila[], int total) {
    char nome[30];
    int i;

    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}
