#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 100

typedef struct {
    int id;
    char nome[50];
    char telefone[20];
    char email[50];   // opcional
} Cliente;

extern Cliente clientes[MAX_CLIENTES];
extern int qtdClientes;

void cadastrarCliente();
void consultarCliente();
void editarCliente();
void listarClientes();       // <-- adicionado
void historicoCompras(int clienteId);
void menuClientes();

#endif
