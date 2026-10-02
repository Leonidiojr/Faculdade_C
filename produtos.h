#ifndef PRODUTOS_H
#define PRODUTOS_H

#define MAX 100

typedef struct {
    int id;
    char nome[50];
    char descricao[200];
    char categoria[30];
    float preco;
    int disponibilidade;   // 1 = disponível, 0 = indisponível
    int quantidade;        // estoque físico
} Produto;


extern Produto produtos[MAX];
extern int qtdProdutos;

void novoProduto();
void editarProduto();
void excluirProduto();
void listarProdutos();
void menuProdutos();

#endif
