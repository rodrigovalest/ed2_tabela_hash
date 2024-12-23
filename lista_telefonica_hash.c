#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Contato {
    char nome[50];
    char telefone[15];
    struct Contato* proximo;
} Contato;

Contato* tabela[TABLE_SIZE] = {NULL};

unsigned int hash(const char* nome) {
    unsigned int hash = 0;
    while (*nome) {
        hash = (hash * 31) + *nome;
        nome++;
    }
    return hash % TABLE_SIZE;
}

void adicionarContato() {
    char nome[50], telefone[15];
    printf("Nome: ");
    scanf("%s", nome);
    printf("Telefone: ");
    scanf("%s", telefone);

    unsigned int indice = hash(nome);
    Contato* novo = (Contato*)malloc(sizeof(Contato));
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char nome[50];
    printf("Nome: ");
    scanf("%s", nome);

    unsigned int indice = hash(nome);
    Contato* atual = tabela[indice];

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Telefone de %s: %s\n", nome, atual->telefone);
            return;
        }
        atual = atual->proximo;
    }
    printf("Erro: Contato '%s' nao encontrado.\n", nome);
}

void removerContato() {
    char nome[50];
    printf("Nome: ");
    scanf("%s", nome);

    unsigned int indice = hash(nome);
    Contato* atual = tabela[indice];
    Contato* anterior = NULL;

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                tabela[indice] = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Erro: Contato '%s' nao encontrado.\n", nome);
}

void exibirContatos() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato* atual = tabela[i];
        while (atual) {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
