#include <stdio.h>
#include <string.h>
#include "pagamentos.h"
#include "pedidos.h"
#include "comprovante.h"

Pagamento pagamentos[MAX_PAGAMENTOS];
int qtdPagamentos = 0;

void registrarPagamento() {
    Pagamento p;
    p.id = qtdPagamentos + 1;

    listarPedidos();

    printf("ID Pedido: ");
    scanf("%d", &p.pedidoId);

    int encontrado = 0;
    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == p.pedidoId) {
            printf("Valor do pedido: R$ %.2f\n", pedidos[i].valorTotal);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Pedido não encontrado! Cancelando pagamento.\n");
        return;
    }

    printf("Valor a pagar (confirme ou altere): ");
    scanf("%f", &p.valor);

    int metodo;
    printf("Método de pagamento:\n");
    printf("1 - Dinheiro\n2 - Débito\n3 - Crédito\n4 - PIX\nEscolha: ");
    scanf("%d", &metodo);

    switch(metodo) {
        case 1: strcpy(p.metodo, "Dinheiro"); break;
        case 2: strcpy(p.metodo, "Debito"); break;
        case 3: strcpy(p.metodo, "Credito"); break;
        case 4: strcpy(p.metodo, "PIX"); break;
        default:
            printf("Método inválido! Pagamento cancelado.\n");
            return;
    }

    pagamentos[qtdPagamentos++] = p;

    // Atualiza status do pedido para "Pago"
    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == p.pedidoId) {
            strcpy(pedidos[i].status, "Pago");
            break;
        }
    }

    printf("Pagamento registrado com sucesso! Pedido %d marcado como Pago.\n", p.pedidoId);
}

void consultarPagamento() {
    int id;
    printf("ID do pagamento: ");
    scanf("%d", &id);
    for (int i = 0; i < qtdPagamentos; i++) {
        if (pagamentos[i].id == id) {
            printf("Pagamento %d | Pedido %d | Valor R$ %.2f | Método: %s\n",
                   pagamentos[i].id, pagamentos[i].pedidoId,
                   pagamentos[i].valor, pagamentos[i].metodo);
                    gerarComprovante(id);
            return;
        }
    }
    printf("Pagamento não encontrado!\n");
}

void menuPagamentos() {
    int op;
    do {
        printf("\n--- Pagamentos ---\n");
        printf("1. Registrar\n2. Consultar\n0. Voltar\nEscolha: ");
        scanf("%d",&op);
        switch(op) {
            case 1: registrarPagamento(); break;
            case 2: consultarPagamento(); break;
        }
    } while(op!=0);
}
