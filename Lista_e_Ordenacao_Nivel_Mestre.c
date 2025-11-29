#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

// Estrutura do componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Assinaturas
void bubbleSortNome(Componente arr[], int n, long *comparacoes);
void insertionSortTipo(Componente arr[], int n, long *comparacoes);
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes);
int buscaBinariaPorNome(Componente arr[], int n, const char chave[], long *comparacoes);
void mostrarComponentes(Componente arr[], int n);

// medirTempo: recebe um ponteiro para função de ordenação que segue o padrão (arr,n,&comparacoes)
double medirTempo(void (*algoritmo)(Componente[], int, long *), Componente arr[], int n, long *comparacoes) {
    clock_t inicio = clock();
    algoritmo(arr, n, comparacoes);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC; // segundos
}

// Funções utilitárias
static void trim_newline(char *s) {
    size_t l = strlen(s);
    if (l > 0 && s[l-1] == '\n') s[l-1] = '\0';
}

// Mostrar vetor
void mostrarComponentes(Componente arr[], int n) {
    printf("\nÍndice | Nome                          | Tipo               | Prioridade\n");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%5d | %-28s | %-17s | %9d\n", i, arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("----------------------------------------------------------------------\n");
}

// Bubble sort por nome (string)
void bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            (*comparacoes)++;
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

// Insertion sort por tipo (string)
void insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(arr[j].tipo, key.tipo) > 0) {
                arr[j+1] = arr[j];
                j--;
            } else break;
        }
        arr[j+1] = key;
    }
}

// Selection sort por prioridade (int) - menor prioridade primeiro (1..10)
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            (*comparacoes)++;
            if (arr[j].prioridade < arr[min_idx].prioridade) min_idx = j;
        }
        if (min_idx != i) {
            Componente tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

// Busca binária por nome - vetor DEVE estar ordenado por nome antes de chamar
int buscaBinariaPorNome(Componente arr[], int n, const char chave[], long *comparacoes) {
    int l = 0, r = n - 1;
    *comparacoes = 0;
    while (l <= r) {
        int m = l + (r - l) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, arr[m].nome);
        if (cmp == 0) return m;
        else if (cmp < 0) r = m - 1;
        else l = m + 1;
    }
    return -1; // não encontrado
}

// Cópia de array (para manter original se o usuário quiser comparar)
void copiarComponentes(Componente dest[], Componente src[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

int main() {
    Componente lista[MAX];
    Componente trabalho[MAX];
    int n = 0;
    char buffer[100];

    printf("=== Módulo: Montagem da Torre de Resgate - Desafio Final ===\n");

    // Cadastro
    printf("Quantos componentes deseja cadastrar? (1-%d): ", MAX);
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    n = atoi(buffer);
    if (n < 1) n = 1;
    if (n > MAX) n = MAX;

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d de %d:\n", i+1, n);
        printf("Nome (ex: chip central): ");
        fgets(lista[i].nome, sizeof(lista[i].nome), stdin);
        trim_newline(lista[i].nome);

        printf("Tipo (ex: controle, suporte, propulsao): ");
        fgets(lista[i].tipo, sizeof(lista[i].tipo), stdin);
        trim_newline(lista[i].tipo);

        printf("Prioridade (1-10): ");
        fgets(buffer, sizeof(buffer), stdin);
        lista[i].prioridade = atoi(buffer);
        if (lista[i].prioridade < 1) lista[i].prioridade = 1;
        if (lista[i].prioridade > 10) lista[i].prioridade = 10;
    }

    // Menu interativo
    int opcao = -1;
    int ordenadoPorNome = 0;
    while (1) {
       printf("                    plano de fuga - codigo da ilha\n"
       "itens na mochila: 0/10\n"
       "status da ordenacao por nome:\n"
       "\n"
       "1. adicionar componente\n"
       "2. descartar componente\n"
       "3. listar componentes (inventario)\n"
       "4. organizar mochila (ordenar componentes)\n"
       "5. busca binaria por componente chave (por nome)\n"
       "0. ativar torre de fuga (sair)\n");
        printf("1 - Ordenar por nome (Bubble Sort)\n");
        printf("2 - Ordenar por tipo (Insertion Sort)\n");
        printf("3 - Ordenar por prioridade (Selection Sort)\n");
        printf("4 - Busca binária por nome (requer ordenação por nome)\n");
        printf("5 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        opcao = atoi(buffer);

        if (opcao == 0) break;

        long comparacoes = 0;
        double tempo = 0.0;

        switch (opcao) {
            case 1: // Bubble sort por nome
                copiarComponentes(trabalho, lista, n);
                tempo = medirTempo(bubbleSortNome, trabalho, n, &comparacoes);
                printf("\nResultado da ordenação por NOME (Bubble Sort):\n");
                mostrarComponentes(trabalho, n);
                printf("Comparações: %ld | Tempo: %.6f s\n", comparacoes, tempo);
                ordenadoPorNome = 1;
                // atualizar lista principal com ordenação se desejar
                copiarComponentes(lista, trabalho, n);
                break;

            case 2: // Insertion sort por tipo
                copiarComponentes(trabalho, lista, n);
                tempo = medirTempo(insertionSortTipo, trabalho, n, &comparacoes);
                printf("\nResultado da ordenação por TIPO (Insertion Sort):\n");
                mostrarComponentes(trabalho, n);
                printf("Comparações: %ld | Tempo: %.6f s\n", comparacoes, tempo);
                ordenadoPorNome = 0;
                copiarComponentes(lista, trabalho, n);
                break;

            case 3: // Selection sort por prioridade
                copiarComponentes(trabalho, lista, n);
                tempo = medirTempo(selectionSortPrioridade, trabalho, n, &comparacoes);
                printf("\nResultado da ordenação por PRIORIDADE (Selection Sort):\n");
                mostrarComponentes(trabalho, n);
                printf("Comparações: %ld | Tempo: %.6f s\n", comparacoes, tempo);
                ordenadoPorNome = 0;
                copiarComponentes(lista, trabalho, n);
                break;

            case 4: ; // Busca binária
                if (!ordenadoPorNome) {
                    printf("\nAtenção: para usar busca binária é necessário ordenar por nome primeiro (opção 1).\n");
                    break;
                }
                printf("\nDigite o NOME do componente-chave para busca: ");
                char chave[30];
                fgets(chave, sizeof(chave), stdin);
                trim_newline(chave);
                // já está ordenado em 'lista' se opção 1 atualizou lista
                int idx = buscaBinariaPorNome(lista, n, chave, &comparacoes);
                printf("\nComparações na busca binária: %ld\n", comparacoes);
                if (idx >= 0) {
                    printf("Componente encontrado no índice %d:\n", idx);
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n", lista[idx].nome, lista[idx].tipo, lista[idx].prioridade);
                } else {
                    printf("Componente '%s' nao encontrado.\n", chave);
                }
                break;

            case 5:
                mostrarComponentes(lista, n);
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    printf("\nEncerrando módulo. Boa sorte na fuga!\n");
    return 0;
}
