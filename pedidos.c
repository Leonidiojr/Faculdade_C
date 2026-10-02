#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pedidos.h"
#include "produtos.h"

Pedido pedidos[MAX_PEDIDOS];
int qtdPedidos = 0;

const char* statusPorNumero(int opcao) {
    switch(opcao) {
        case 1: return "Recebido";
        case 2: return "Em preparação";
        case 3: return "Pronto para entrega";
        case 4: return "Entregue";
        case 5: return "Cancelado";
        default: return "Desconhecido";
    }
}

void criarPedido() {
    Pedido p;
    p.id = ++qtdPedidos;
    p.qtdItens = 0;
    p.valorTotal = 0.0;
    strcpy(p.status, "Recebido"); // status inicial

    // Data e hora atuais
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(p.dataHora, sizeof(p.dataHora), "%d/%m/%Y %H:%M", t);

    printf("ID do cliente (0 se não informado): ");
    scanf("%d", &p.clienteId);

    pedidos[p.id - 1] = p;
    printf("Pedido %d criado com status inicial: %s\n", p.id, p.status);

    adicionarItem(p.id);
}

void adicionarItem(int pedidoId) {
    int prodId, qtd;
    listarProdutosEstoque();
    printf("Código do produto: ");
    scanf("%d", &prodId);
    printf("Quantidade: ");
    scanf("%d", &qtd);

    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == pedidoId) {
            for (int j = 0; j < qtdProdutos; j++) {
                if (produtos[j].id == prodId && produtos[j].disponibilidade == 1) {
                    if (produtos[j].quantidade >= qtd) {
                        ItemPedido item;
                        item.produtoId = prodId;
                        item.quantidade = qtd;
                        item.subtotal = produtos[j].preco * qtd;
                        pedidos[i].itens[pedidos[i].qtdItens++] = item;
                        pedidos[i].valorTotal += item.subtotal;

                        // Atualiza estoque
                        produtos[j].quantidade -= qtd;

                        printf("Item adicionado! Subtotal R$ %.2f\n", item.subtotal);
                    } else {
                        printf("Estoque insuficiente! Disponível: %d\n", produtos[j].quantidade);
                    }
                    return;
                }
            }
            printf("Produto não encontrado ou indisponível!\n");
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}

void removerItem(int pedidoId) {
    int prodId;
    printf("Código do produto a remover: ");
    scanf("%d", &prodId);

    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == pedidoId) {
            for (int j = 0; j < pedidos[i].qtdItens; j++) {
                if (pedidos[i].itens[j].produtoId == prodId) {
                    // Atualiza valor total do pedido
                    pedidos[i].valorTotal -= pedidos[i].itens[j].subtotal;

                    // Repor estoque do produto
                    for (int k = 0; k < qtdProdutos; k++) {
                        if (produtos[k].id == prodId) {
                            produtos[k].quantidade += pedidos[i].itens[j].quantidade;
                            break;
                        }
                    }

                    // Remover item do array
                    for (int k = j; k < pedidos[i].qtdItens - 1; k++) {
                        pedidos[i].itens[k] = pedidos[i].itens[k+1];
                    }
                    pedidos[i].qtdItens--;

                    printf("Item removido e estoque atualizado!\n");
                    calcularTotal(pedidoId);
                    return;
                }
            }
            printf("Item não encontrado!\n");
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}

void atualizarStatus(int pedidoId) {
    int opcao;
    printf("Escolha o novo status:\n");
    printf("1 - Recebido\n2 - Em preparação\n3 - Pronto para entrega\n4 - Entregue\n5 - Cancelado\n");
    scanf("%d", &opcao);

    const char* novoStatus = statusPorNumero(opcao);

    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == pedidoId) {
            strcpy(pedidos[i].status, novoStatus);
            printf("Status do pedido %d atualizado para %s!\n", pedidoId, novoStatus);
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}

void calcularTotal(int pedidoId) {
    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == pedidoId) {
            float total = 0.0;
            for (int j = 0; j < pedidos[i].qtdItens; j++) {
                total += pedidos[i].itens[j].subtotal;
            }
            pedidos[i].valorTotal = total;
            printf("Valor total do pedido %d: R$ %.2f\n", pedidoId, total);
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}

void consultarPedidoPorNumero() {
    int id;
    printf("Número do pedido: ");
    scanf("%d", &id);
    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == id) {
            printf("Pedido %d | Cliente %d | Valor R$ %.2f | Status %s | Data %s\n",
                   pedidos[i].id, pedidos[i].clienteId,
                   pedidos[i].valorTotal, pedidos[i].status, pedidos[i].dataHora);
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}

void consultarPedidoPorCliente() {
    int clienteId;
    printf("ID do cliente: ");
    scanf("%d", &clienteId);
    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].clienteId == clienteId) {
            printf("Pedido %d | Valor R$ %.2f | Status %s | Data %s\n",
                   pedidos[i].id, pedidos[i].valorTotal,
                   pedidos[i].status, pedidos[i].dataHora);
        }
    }
}

void consultarPedidoPorData() {
    char data[20];
    printf("Data (dd/mm/aaaa): ");
    scanf(" %[^\n]", data);
    for (int i = 0; i < qtdPedidos; i++) {
        if (strncmp(pedidos[i].dataHora, data, 10) == 0) {
            printf("Pedido %d | Cliente %d | Valor R$ %.2f | Status %s | Data %s\n",
                   pedidos[i].id, pedidos[i].clienteId,
                   pedidos[i].valorTotal, pedidos[i].status, pedidos[i].dataHora);
        }
    }
}

void consultarPedidoPorStatus() {
    int opcao;
    printf("Escolha o status:\n");
    printf("1 - Recebido\n2 - Em preparação\n3 - Pronto para entrega\n4 - Entregue\n5 - Cancelado\n");
    scanf("%d", &opcao);

    const char* status = statusPorNumero(opcao);

    for (int i = 0; i < qtdPedidos; i++) {
        if (strcmp(pedidos[i].status, status) == 0) {
            printf("Pedido %d | Cliente %d | Valor R$ %.2f | Status %s | Data %s\n",
                   pedidos[i].id, pedidos[i].clienteId,
                   pedidos[i].valorTotal, pedidos[i].status, pedidos[i].dataHora);
        }
    }
}

void listarPedidos() {
    printf("\n--- Lista de Pedidos ---\n");
    for (int i = 0; i < qtdPedidos; i++) {
        printf("Pedido %d | Cliente %d | Valor R$ %.2f | Status %s | Data %s\n",
               pedidos[i].id, pedidos[i].clienteId,
               pedidos[i].valorTotal, pedidos[i].status, pedidos[i].dataHora);
    }
    if (qtdPedidos == 0) {
        printf("Nenhum pedido registrado.\n");
    }
}

void menuPedidos() {
    int op, id;
    do {
        printf("\n--- Pedidos ---\n");
        printf("1. Criar\n2. Adicionar Item\n3. Remover Item\n4. Atualizar Status\n5. Calcular Total\n6. Consultar por Número\n7. Consultar por Cliente\n8. Consultar por Data\n9. Consultar por Status\n10. Listar\n0. Voltar\nEscolha: ");
        scanf("%d",&op);
        switch(op) {
            case 1: criarPedido(); break;
            case 2: printf("ID do pedido: "); scanf("%d",&id); adicionarItem(id); break;
            case 3: printf("ID do pedido: "); scanf("%d",&id); removerItem(id); break;
            case 4: printf("ID do pedido: "); scanf("%d",&id); atualizarStatus(id); break;
            case 5: printf("ID do pedido: "); scanf("%d",&id); calcularTotal(id); break;
            case 6: consultarPedidoPorNumero(); break;
            case 7: consultarPedidoPorCliente(); break;
            case 8: consultarPedidoPorData(); break;
            case 9: consultarPedidoPorStatus(); break;
            case 10: listarPedidos(); break;
        }
    } while(op!=0);
}
