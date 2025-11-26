#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10   // limite da mochila

//-------------------------------------------------
// STRUCT
//-------------------------------------------------

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

//-------------------------------------------------
// VARIÁVEIS GLOBAIS
//-------------------------------------------------

Item mochila[MAX];
int tamanho = 0;

//-------------------------------------------------
// FUNÇÕES
//-------------------------------------------------

void mostrarMenu() {
    printf("\nItens na mochila: %d/%d\n\n", tamanho, MAX);
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens da mochila\n");
    printf("4. Buscar item por nome\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void adicionarItem() {
    if (tamanho >= MAX) {
        printf("A mochila esta cheia!\n");
        return;
    }

    Item x;
    printf("Nome: ");
    scanf("%s", x.nome);
    printf("Tipo: ");
    scanf("%s", x.tipo);
    printf("Quantidade: ");
    scanf("%d", &x.quantidade);

    mochila[tamanho] = x;
    tamanho++;

    printf("Item adicionado!\n");
}

void removerItem() {
    char nome[30];
    printf("Nome do item para remover: ");
    scanf("%s", nome);

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < tamanho - 1; j++)
                mochila[j] = mochila[j + 1];
            tamanho--;
            printf("Item removido!\n");
            return;
        }
    }

    printf("Item nao encontrado.\n");
}

void listarItens() {
    if (tamanho == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

void buscarItem() {
    char nome[30];
    printf("Nome do item para buscar: ");
    scanf("%s", nome);

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado.\n");
}

//-------------------------------------------------
// MAIN
//-------------------------------------------------

int main() {
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            adicionarItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            listarItens();
            break;
        case 4:
            buscarItem();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
