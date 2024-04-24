#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

void ordenarItensEstoque(ItemEstoque *estoque) {
    if (estoque == NULL || estoque->prox == NULL) {
        printf("Estoque vazio ou com apenas um item. Nada a apresentar.\n");
        return;
    }

    int trocado;
    ItemEstoque *ptr;
    ItemEstoque *ult = NULL;

    do {
        trocado = 0;
        ptr = estoque;

        while (ptr->prox != ult) {
            if (strcmp(ptr->nome, ptr->prox->nome) > 0) {
                ItemEstoque *temp = (ItemEstoque *)malloc(sizeof(ItemEstoque));
                if (temp == NULL) {
                    printf("Erro ao alocar memória para ordenar estoque.\n");
                    return;
                }
                strcpy(temp->nome, ptr->nome);
                temp->quantidade = ptr->quantidade;
                temp->valor_unitario = ptr->valor_unitario;

                strcpy(ptr->nome, ptr->prox->nome);
                ptr->quantidade = ptr->prox->quantidade;
                ptr->valor_unitario = ptr->prox->valor_unitario;

                strcpy(ptr->prox->nome, temp->nome);
                ptr->prox->quantidade = temp->quantidade;
                ptr->prox->valor_unitario = temp->valor_unitario;

                free(temp);
                trocado = 1;
            }
            ptr = ptr->prox;
        }
        ult = ptr;
    } while (trocado);
}

void adicionarItemEstoque(ItemEstoque **estoque, char nome[], int quantidade, float valor_unitario) {
    ItemEstoque *novoItem = (ItemEstoque *)malloc(sizeof(ItemEstoque));
    if (novoItem == NULL) {
        printf("Erro ao alocar memória para novo item.\n");
        return;
    }

    strcpy(novoItem->nome, nome);
    novoItem->quantidade = quantidade;
    novoItem->valor_unitario = valor_unitario;
    novoItem->prox = NULL;

    if (*estoque == NULL) {
        *estoque = novoItem;
    } else {
        ItemEstoque *atual = *estoque;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoItem;
    }
}

void removerItemEstoque(ItemEstoque **estoque, char nome[]) {
    if (*estoque == NULL) {
        printf("Estoque vazio. Nada para remover.\n");
        return;
    }

    ItemEstoque *atual = *estoque;
    ItemEstoque *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Item \"%s\" não encontrado no estoque.\n", nome);
        return;
    }

    if (anterior == NULL) {
        *estoque = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Item \"%s\" removido do estoque.\n", nome);
}

void listarItensEstoque(ItemEstoque *estoque) {
    ItemEstoque *atual = estoque;
    while (atual != NULL) {
        printf("%s - Quantidade: %d - Valor Unitário: R$ %.2f\n", atual->nome, atual->quantidade, atual->valor_unitario);
        atual = atual->prox;
    }
}

float calcularValorTotalEstoque(ItemEstoque *estoque) {
    float valor_total = 0.0;
    ItemEstoque *atual = estoque;
    while (atual != NULL) {
        valor_total += atual->quantidade * atual->valor_unitario;
        atual = atual->prox;
    }
    return valor_total;
}

void imprimirEstoqueArquivo(ItemEstoque *estoque) {
    FILE *arquivo;
    arquivo = fopen("estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "-- Estoque Atual --\n");
    ItemEstoque *atual = estoque;
    while (atual != NULL) {
        fprintf(arquivo, "%s - Quantidade: %d - Valor Unitário: R$ %.2f\n", atual->nome, atual->quantidade, atual->valor_unitario);
        atual = atual->prox;
    }

    fclose(arquivo);
    printf("Estoque exibido e salvo com sucesso no arquivo 'estoque.txt'.\n");
}
