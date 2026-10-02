#include <stdio.h>
#include <string.h>
#include "relatorios.h"
#include "pagamentos.h"
#include "pedidos.h"
#include "produtos.h"

extern Pagamento pagamentos[];
extern int qtdPagamentos;
extern Pedido pedidos[];
extern int qtdPedidos;
extern Produto produtos[];
extern int qtdProdutos;

void gerarHistorico() {
    printf("Gerando histórico de vendas (simulação)...\n");
}

void consultarVendas() {
    float total = 0;

    printf("\n=== Relatório de Vendas ===\n");
    for (int i = 0; i < qtdPagamentos; i++) {
        printf("Pagamento %d | Pedido %d | Valor R$ %.2f | Método: %s\n",
               pagamentos[i].id,
               pagamentos[i].pedidoId,
               pagamentos[i].valor,
               pagamentos[i].metodo);
        total += pagamentos[i].valor;
    }
    printf("Total de Vendas: R$ %.2f\n", total);

    // Calcular produtos vendidos
    int vendasPorProduto[qtdProdutos];
    for (int i = 0; i < qtdProdutos; i++) {
        vendasPorProduto[i] = 0;
    }

    for (int i = 0; i < qtdPedidos; i++) {
        for (int j = 0; j < pedidos[i].qtdItens; j++) {
            int prodId = pedidos[i].itens[j].produtoId;
            int qtdVendida = pedidos[i].itens[j].quantidade;
            for (int k = 0; k < qtdProdutos; k++) {
                if (produtos[k].id == prodId) {
                    vendasPorProduto[k] += qtdVendida;
                    break;
                }
            }
        }
    }

    printf("\n--- Produtos Mais Vendidos ---\n");
    for (int i = 0; i < qtdProdutos; i++) {
        if (vendasPorProduto[i] > 0) {
            printf("%s => Vendidos: %d unidades\n",
                   produtos[i].nome,
                   vendasPorProduto[i]);
        }
    }

    printf("\n--- Produtos Menos Vendidos ---\n");
    for (int i = 0; i < qtdProdutos; i++) {
        if (vendasPorProduto[i] == 0) {
            printf("%s => Nenhuma venda registrada\n", produtos[i].nome);
        }
    }

    // Modalidade de pagamento preferida
    int countPIX = 0, countDebito = 0, countCredito = 0, countDinheiro = 0;
    for (int i = 0; i < qtdPagamentos; i++) {
        if (strcmp(pagamentos[i].metodo, "PIX") == 0) countPIX++;
        else if (strcmp(pagamentos[i].metodo, "Debito") == 0) countDebito++;
        else if (strcmp(pagamentos[i].metodo, "Credito") == 0) countCredito++;
        else if (strcmp(pagamentos[i].metodo, "Dinheiro") == 0) countDinheiro++;
    }

    printf("\n--- Modalidade de Pagamento Preferida ---\n");
    if (countPIX >= countDebito && countPIX >= countCredito && countPIX >= countDinheiro)
        printf("PIX foi o método mais utilizado (%d vezes)\n", countPIX);
    else if (countDebito >= countPIX && countDebito >= countCredito && countDebito >= countDinheiro)
        printf("Débito foi o método mais utilizado (%d vezes)\n", countDebito);
    else if (countCredito >= countPIX && countCredito >= countDebito && countCredito >= countDinheiro)
        printf("Crédito foi o método mais utilizado (%d vezes)\n", countCredito);
    else
        printf("Dinheiro foi o método mais utilizado (%d vezes)\n", countDinheiro);
    graficoPagamentos(countPIX, countDebito, countCredito, countDinheiro);

    // Mostrar estoque atual
    printf("\n--- Estoque Atual ---\n");
    for (int i = 0; i < qtdProdutos; i++) {
        printf("Produto %d | %s | Preço R$ %.2f | Disponível: %s\n",
               produtos[i].id,
               produtos[i].nome,
               produtos[i].preco,
               produtos[i].disponibilidade ? "Sim" : "Não");
    }


}

void graficoPagamentos(int countPIX, int countDebito, int countCredito, int countDinheiro) {
    int valores[4] = {countPIX, countDebito, countCredito, countDinheiro};
    char *labels[4] = {"PIX", "Deb", "Cred", "Din"};

    // Encontrar o maior valor para escalar
    int max = valores[0];
    for (int i = 1; i < 4; i++) {
        if (valores[i] > max) max = valores[i];
    }

    printf("\n=== Gráfico de Modalidades de Pagamento ===\n");
    for (int nivel = max; nivel > 0; nivel--) {
        for (int i = 0; i < 4; i++) {
            if (valores[i] >= nivel)
                printf("  #  ");
            else
                printf("     ");
        }
        printf("\n");
    }

    for (int i = 0; i < 4; i++) {
        printf("-----");
    }
    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("%3s  ", labels[i]);
    }
    printf("\n");
}