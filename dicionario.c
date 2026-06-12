#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10

// NÓS 
typedef struct No {
    char palavra[50];
    char definicao[200];
    struct No *prox;
} No;

// CRIAR NÓ
No *criarNo(char palavra[], char definicao[]) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL)
    {
        fprintf(stderr, "Erro: malloc falhou\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novo->palavra, palavra);
    strcpy(novo->definicao, definicao);

    novo->prox = NULL;

    return novo;
}

// TABELA

typedef struct TabelaHash
{
    int tamanho;
    int elementos;
    int colisoes;
    No **buckets;
} TabelaHash;

// CRIA A TABELA
TabelaHash *criarTabela(int tamanho) {
    TabelaHash *tabela = malloc(sizeof(TabelaHash));

    if (tabela == NULL)
    {
        fprintf(stderr, "Erro: malloc falhou\n");
        exit(EXIT_FAILURE);
    }

    tabela->tamanho = tamanho;
    tabela->elementos = 0;
    tabela->colisoes = 0;

    tabela->buckets = calloc(tamanho, sizeof(No *));

    if (tabela->buckets == NULL)
    {
        fprintf(stderr, "Erro: calloc falhou\n");
        free(tabela);
        exit(EXIT_FAILURE);
    }

    return tabela;
}


// função hash
int hashString(TabelaHash *tabela, char palavra[])
{
    int soma = 0;

    for (int i=0; palavra[i] != '\0'; i++) {
        soma += palavra[i];
    }
    return soma % tabela->tamanho;
}

// INSERIR, BUSCAR, REMOVER, EXIBIR E LIBERAR

// INSERIR
void inserir(TabelaHash *tabela, char palavra[], char definicao[]) {
    int indice = hashString(tabela, palavra);
    No *atual = tabela->buckets[indice];

    while (atual != NULL)
    {
        if (strcmp(atual->palavra, palavra) == 0)
        {
            strcpy(atual->definicao, definicao);
            return;
        }
        atual = atual->prox;
    }
    if (tabela->buckets[indice] != NULL)
    {
        tabela->colisoes++;
    }

    No *novo = criarNo(palavra, definicao);

    novo->prox = tabela->buckets[indice];
    tabela->buckets[indice] = novo;

    tabela->elementos++;
}

// BUSCAR
No *buscar(TabelaHash *tabela, char palavra[]) {
    int indice = hashString(tabela, palavra);
    No *atual = tabela->buckets[indice];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return atual;
        }

        atual = atual->prox;

    }
    return NULL;
}

// REMOVER
int remover(TabelaHash *tabela, char palavra[]) {
    int indice = hashString(tabela, palavra);
    No *atual = tabela->buckets[indice];
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            if (anterior == NULL)
                tabela->buckets[indice] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            tabela->elementos--;
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}

// IMPRIMIR
void imprimirTabela(TabelaHash *tabela)
{
    for (int i = 0; i < tabela->tamanho; i++)
    {
        printf("[%d] -> ", i);
        No *atual = tabela->buckets[i];

        if (atual == NULL)
        {
            printf("vazio");
        }
        else
        {
            while (atual != NULL)
            {
                printf("(%s, %s)", atual->palavra, atual->definicao);
                if (atual->prox != NULL)
                    printf(" -> ");
                atual = atual->prox;
            }
        }

        printf("\n");
    }
}

// MOSTRAR ESTATISTICAS
void mostrarEstatisticas(TabelaHash *tabela)
{
    int maiorLista = 0;

    for (int i = 0; i < tabela->tamanho; i++)
    {
        int contador = 0;
        No *atual = tabela->buckets[i];

        while (atual != NULL)
        {
            contador++;
            atual = atual->prox;
        }

        if (contador > maiorLista)
        {
            maiorLista = contador;
        }
    }

    float fatorCarga = (float)tabela->elementos / tabela->tamanho;

    printf("\n=== Estatisticas da Tabela ===\n");
    printf("Quantidade de elementos: %d\n", tabela->elementos);
    printf("Quantidade de colisoes: %d\n", tabela->colisoes);
    printf("Fator de carga: %.2f\n", fatorCarga);
    printf("Maior lista encadeada: %d\n", maiorLista);
}

// MAIN
int main()
{
    TabelaHash *tabela = criarTabela(10);

    int opcao;
    char palavra[50];
    char definicao[200];

    do
    {
        printf("\n=== DICIONARIO HASH ===\n");
        printf("1 - Inserir palavra\n");
        printf("2 - Buscar palavra\n");
        printf("3 - Remover palavra\n");
        printf("4 - Exibir tabela\n");
        printf("5 - Exibir estatisticas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome o '\n'

        switch (opcao)
        {
        case 1:
            printf("Palavra: ");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            printf("Definicao: ");
            fgets(definicao, sizeof(definicao), stdin);
            definicao[strcspn(definicao, "\n")] = '\0';

            inserir(tabela, palavra, definicao);
            printf("Palavra inserida com sucesso!\n");
            break;

        case 2:
        {
            printf("Palavra a buscar: ");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            No *resultado = buscar(tabela, palavra);

            if (resultado != NULL)
            {
                printf("Palavra: %s\n", resultado->palavra);
                printf("Definicao: %s\n", resultado->definicao);
            }
            else
            {
                printf("Palavra nao encontrada.\n");
            }

            break;
        }

        case 3:
            printf("Palavra a remover: ");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            if (remover(tabela, palavra))
            {
                printf("Palavra removida com sucesso.\n");
            }
            else
            {
                printf("Palavra nao encontrada.\n");
            }

            break;

        case 4:
            imprimirTabela(tabela);
            break;

        case 5:
            mostrarEstatisticas(tabela);
            break;

        case 0:
            printf("Encerrando programa...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}