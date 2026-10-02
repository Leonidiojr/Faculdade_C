#ifndef PAGAMENTOS_H
#define PAGAMENTOS_H

#define MAX_PAGAMENTOS 100

typedef struct {
    int id;
    int pedidoId;
    float valor;
    char metodo[20];   // Dinheiro, Débito, Crédito, PIX
} Pagamento;

extern Pagamento pagamentos[MAX_PAGAMENTOS];
extern int qtdPagamentos;

void registrarPagamento();
void consultarPagamento();
void menuPagamentos();

#endif
