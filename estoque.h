#ifndef ESTOQUE_H
#define ESTOQUE_H

typedef struct ItemEstoque {
    char nome[100];
    int quantidade;
    float valor_unitario;
    struct ItemEstoque *prox;
} ItemEstoque;

void ordenarItensEstoque(ItemEstoque *estoque);
void adicionarItemEstoque(ItemEstoque **estoque, char nome[], int quantidade, float valor_unitario);
void removerItemEstoque(ItemEstoque **estoque, char nome[]);
void listarItensEstoque(ItemEstoque *estoque);
float calcularValorTotalEstoque(ItemEstoque *estoque);
void imprimirEstoqueArquivo(ItemEstoque *estoque);

#endif
