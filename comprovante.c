#include <stdio.h>
#include "comprovante.h"
#include "pagamentos.h"
#include "pedidos.h"
#include "clientes.h"
#include "produtos.h"

extern Pagamento pagamentos[];
extern int qtdPagamentos;
extern Pedido pedidos[];
extern int qtdPedidos;
extern Cliente clientes[];
extern int qtdClientes;
extern Produto produtos[];
extern int qtdProdutos;

void gerarComprovante(int pedidoId) {
    // Buscar pedido
    Pedido *pedido = NULL;
    for (int j = 0; j < qtdPedidos; j++) {
        if (pedidos[j].id == pedidoId) {
            pedido = &pedidos[j];
            break;
        }
    }
    if (!pedido) {
        printf("Pedido não encontrado!\n");
        return;
    }

    // Buscar cliente
    Cliente *cliente = NULL;
    for (int k = 0; k < qtdClientes; k++) {
        if (clientes[k].id == pedido->clienteId) {
            cliente = &clientes[k];
            break;
        }
    }

    // Buscar pagamento associado
    Pagamento *pagamento = NULL;
    for (int i = 0; i < qtdPagamentos; i++) {
        if (pagamentos[i].pedidoId == pedidoId) {
            pagamento = &pagamentos[i];
            break;
        }
    }

    printf("\n================================================\n");
    printf("             COMPROVANTE DO PEDIDO    \n");
    printf("==================================================\n");

    if (cliente)
        printf("Cliente: %s \nTelefone: %s \nEmail: %s\n",
               cliente->nome, cliente->telefone, cliente->email);

    printf("\nPedido Nº: %d | Data/Hora: %s\n", pedido->id, pedido->dataHora);
    printf("Status do Pedido: %s\n", pedido->status);
    printf("Itens:\n");
    for (int j = 0; j < pedido->qtdItens; j++) {
        int prodId = pedido->itens[j].produtoId;
        Produto *prod = NULL;
        for (int m = 0; m < qtdProdutos; m++) {
            if (produtos[m].id == prodId) {
                prod = &produtos[m];
                break;
            }
        }
        if (prod) {
            printf(" - %s | Qtd: %d | Subtotal: R$ %.2f\n",
                   prod->nome,
                   pedido->itens[j].quantidade,
                   pedido->itens[j].subtotal);
        }
    }

    printf("------------------------------------\n");
    if (pagamento) {
        printf("Pagamento ID: %d\n", pagamento->id);
        printf("Valor Pago: R$ %.2f\n", pagamento->valor);
        printf("Método: %s\n", pagamento->metodo);
    } else {
        printf("Pagamento ainda não registrado!\n");
    }
    printf("====================================\n\n");
}
