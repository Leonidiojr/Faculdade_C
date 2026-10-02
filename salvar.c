#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "produtos.h"
#include "pedidos.h"
#include "pagamentos.h"

void salvarDados() {
    FILE *f = fopen("dados.txt", "w");
    if (!f) {
        printf("Erro ao salvar dados!\n");
        return;
    }

    // Salvar clientes
    fprintf(f, "CLIENTES %d\n", qtdClientes);
    for (int i = 0; i < qtdClientes; i++) {
        fprintf(f, "%d;%s;%s;%s\n",
                clientes[i].id,
                clientes[i].nome,
                clientes[i].telefone,
                clientes[i].email);
    }

    // Salvar produtos (inclui quantidade em estoque)
    fprintf(f, "PRODUTOS %d\n", qtdProdutos);
    for (int i = 0; i < qtdProdutos; i++) {
        fprintf(f, "%d;%s;%s;%s;%.2f;%d;%d\n",
                produtos[i].id,
                produtos[i].nome,
                produtos[i].descricao,
                produtos[i].categoria,
                produtos[i].preco,
                produtos[i].disponibilidade,
                produtos[i].quantidade);
    }

    // Salvar pedidos
    fprintf(f, "PEDIDOS %d\n", qtdPedidos);
    for (int i = 0; i < qtdPedidos; i++) {
        fprintf(f, "%d;%s;%d;%d;%.2f;%s\n",
                pedidos[i].id,
                pedidos[i].dataHora,
                pedidos[i].clienteId,
                pedidos[i].qtdItens,
                pedidos[i].valorTotal,
                pedidos[i].status);
        for (int j = 0; j < pedidos[i].qtdItens; j++) {
            fprintf(f, "ITEM;%d;%d;%.2f\n",
                    pedidos[i].itens[j].produtoId,
                    pedidos[i].itens[j].quantidade,
                    pedidos[i].itens[j].subtotal);
        }
    }

    // Salvar pagamentos
    fprintf(f, "PAGAMENTOS %d\n", qtdPagamentos);
    for (int i = 0; i < qtdPagamentos; i++) {
        fprintf(f, "%d;%d;%.2f;%s\n",
                pagamentos[i].id,
                pagamentos[i].pedidoId,
                pagamentos[i].valor,
                pagamentos[i].metodo);
    }

    fclose(f);
}

void carregarDados() {
    FILE *f = fopen("dados.txt", "r");
    if (!f) {
        printf("Nenhum arquivo de dados encontrado, iniciando vazio.\n");
        return;
    }

    char tipo[20];
    while (fscanf(f, "%19s", tipo) == 1) {
        if (strcmp(tipo, "CLIENTES") == 0) {
            fscanf(f, "%d", &qtdClientes);
            for (int i = 0; i < qtdClientes; i++) {
                fscanf(f, "%d;%49[^;];%19[^;];%49[^\n]\n",
                       &clientes[i].id,
                       clientes[i].nome,
                       clientes[i].telefone,
                       clientes[i].email);
            }
        } else if (strcmp(tipo, "PRODUTOS") == 0) {
            fscanf(f, "%d", &qtdProdutos);
            for (int i = 0; i < qtdProdutos; i++) {
                fscanf(f, "%d;%49[^;];%99[^;];%19[^;];%f;%d;%d\n",
                       &produtos[i].id,
                       produtos[i].nome,
                       produtos[i].descricao,
                       produtos[i].categoria,
                       &produtos[i].preco,
                       &produtos[i].disponibilidade,
                       &produtos[i].quantidade);
            }
        } else if (strcmp(tipo, "PEDIDOS") == 0) {
            fscanf(f, "%d", &qtdPedidos);
            for (int i = 0; i < qtdPedidos; i++) {
                fscanf(f, "%d;%19[^;];%d;%d;%f;%29[^\n]\n",
                       &pedidos[i].id,
                       pedidos[i].dataHora,
                       &pedidos[i].clienteId,
                       &pedidos[i].qtdItens,
                       &pedidos[i].valorTotal,
                       pedidos[i].status);
                for (int j = 0; j < pedidos[i].qtdItens; j++) {
                    fscanf(f, "ITEM;%d;%d;%f\n",
                           &pedidos[i].itens[j].produtoId,
                           &pedidos[i].itens[j].quantidade,
                           &pedidos[i].itens[j].subtotal);
                }
            }
        } else if (strcmp(tipo, "PAGAMENTOS") == 0) {
            fscanf(f, "%d", &qtdPagamentos);
            for (int i = 0; i < qtdPagamentos; i++) {
                fscanf(f, "%d;%d;%f;%19[^\n]\n",
                       &pagamentos[i].id,
                       &pagamentos[i].pedidoId,
                       &pagamentos[i].valor,
                       pagamentos[i].metodo);
            }
        }
    }

    fclose(f);
}
