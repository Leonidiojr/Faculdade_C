#include <stdio.h>
#include <string.h>
#include "produtos.h"

Produto produtos[MAX];
int qtdProdutos = 0;

void novoProduto() {
    Produto p;
    p.id = ++qtdProdutos;
    printf("Código: %d\n", p.id);

    printf("Nome: ");
    scanf(" %[^\n]", p.nome);

    printf("Descrição: ");
    scanf(" %[^\n]", p.descricao);

    printf("Categoria (bebida/lanche/sobremesa): ");
    scanf(" %[^\n]", p.categoria);

    printf("Preço: ");
    scanf("%f", &p.preco);

    printf("Disponibilidade (1=Sim, 0=Não): ");
    scanf("%d", &p.disponibilidade);

    printf("Quantidade em estoque: ");
    scanf("%d", &p.quantidade);

    produtos[qtdProdutos-1] = p;
    printf("Produto cadastrado com sucesso!\n");
    printf("Estoque inicial: %d unidades\n", p.quantidade);
}


void editarProduto() {
    int id;
    printf("Código do produto: ");
    scanf("%d", &id);

    for (int i = 0; i < qtdProdutos; i++) {
        if (produtos[i].id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", produtos[i].nome);

            printf("Nova descrição: ");
            scanf(" %[^\n]", produtos[i].descricao);

            printf("Nova categoria: ");
            scanf(" %[^\n]", produtos[i].categoria);

            printf("Novo preço: ");
            scanf("%f", &produtos[i].preco);

            printf("Disponibilidade (1=Sim, 0=Não): ");
            scanf("%d", &produtos[i].disponibilidade);

            printf("Nova quantidade em estoque: ");
            scanf("%d", &produtos[i].quantidade);

            printf("Produto atualizado!\n");
            printf("Estoque atual: %d unidades\n", produtos[i].quantidade);
            return;
        }
    }
    printf("Produto não encontrado.\n");
}


void excluirProduto() {
    int id;
    printf("Código do produto: "); scanf("%d", &id);
    for (int i=0; i<qtdProdutos; i++) {
        if (produtos[i].id == id) {
            for (int j=i; j<qtdProdutos-1; j++)
                produtos[j] = produtos[j+1];
            qtdProdutos--;
            printf("Produto excluído!\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void listarProdutos() {
    printf("\n--- Lista de Produtos ---\n");
    for (int i = 0; i < qtdProdutos; i++) {
        printf("Código: %d | Nome: %s | Categoria: %s | Preço: R$%.2f | Disponível: %s | Estoque: %d unidades\n",
               produtos[i].id,
               produtos[i].nome,
               produtos[i].categoria,
               produtos[i].preco,
               produtos[i].disponibilidade ? "Sim" : "Não",
               produtos[i].quantidade);
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("-----------------------------------\n");
    }
}

void listarProdutosEstoque() {
    printf("\n--- Lista de Produtos ---\n");
    for (int i = 0; i < qtdProdutos; i++) {
        if ((produtos[i].quantidade > 0) && (produtos[i].disponibilidade > 0)) {
            printf("Código: %d | Nome: %s | Categoria: %s | Preço: R$%.2f | Disponível: %s | Estoque: %d unidades\n",
                   produtos[i].id,
                   produtos[i].nome,
                   produtos[i].categoria,
                   produtos[i].preco,
                   produtos[i].disponibilidade ? "Sim" : "Não",
                   produtos[i].quantidade);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("-----------------------------------\n");
        }
    }
}

void menuProdutos() {
    int op;
    do {
        printf("\n--- Produtos ---\n");
        printf("1. Novo\n2. Editar\n3. Excluir\n4. Listar\n0. Voltar\nEscolha: ");
        scanf("%d",&op);
        switch(op) {
            case 1: novoProduto(); break;
            case 2: editarProduto(); break;
            case 3: excluirProduto(); break;
            case 4: listarProdutos(); break;
        }
    } while(op!=0);
}
