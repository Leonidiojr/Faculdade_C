#include <stdio.h>
#include "estoque.h"
#include "produtos.h"

extern Produto produtos[];
extern int qtdProdutos;

void atualizarEstoque(int produtoId, int quantidade) {
    for (int i = 0; i < qtdProdutos; i++) {
        if (produtos[i].id == produtoId) {
            produtos[i].quantidade += quantidade;
            printf("Estoque atualizado! Novo estoque: %d\n", produtos[i].quantidade);
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void consultarEstoque() {
    printf("\n--- Estoque ---\n");
    for (int i = 0; i < qtdProdutos; i++) {
        printf("Produto %d | %s | Qtd: %d | Disponível: %s\n",
               produtos[i].id, produtos[i].nome, produtos[i].quantidade,
               produtos[i].disponibilidade ? "Sim" : "Não");
    }
}
