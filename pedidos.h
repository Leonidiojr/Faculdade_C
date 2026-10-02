#ifndef PEDIDOS_H
#define PEDIDOS_H

#define MAX_PEDIDOS 100
#define MAX_ITENS   20

typedef struct {
    int produtoId;
    int quantidade;
    float subtotal;
} ItemPedido;

typedef struct {
    int id;
    char dataHora[20];
    int clienteId;
    ItemPedido itens[MAX_ITENS];
    int qtdItens;
    float valorTotal;
    char status[30];
} Pedido;

extern Pedido pedidos[MAX_PEDIDOS];
extern int qtdPedidos;

void criarPedido();
void adicionarItem(int pedidoId);
void removerItem(int pedidoId);
void atualizarStatus(int pedidoId);   // <-- ajustado para só receber pedidoId
void calcularTotal(int pedidoId);
void consultarPedidoPorNumero();
void consultarPedidoPorCliente();
void consultarPedidoPorData();
void consultarPedidoPorStatus();
void listarPedidos();
void listarProdutosEstoque();
void menuPedidos();

#endif
