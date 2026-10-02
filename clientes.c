#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "pedidos.h"
#include "produtos.h"
#include "pagamentos.h"

extern Cliente clientes[];
extern int qtdClientes;
extern Pedido pedidos[];
extern int qtdPedidos;
extern Produto produtos[];
extern int qtdProdutos;
extern Pagamento pagamentos[];
extern int qtdPagamentos;


Cliente clientes[MAX_CLIENTES];
int qtdClientes = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void cadastrarCliente() {
    Cliente c;
    c.id = qtdClientes + 1;

    printf("Nome: ");
    scanf(" %[^\n]", c.nome);

    printf("Telefone: ");
    scanf(" %[^\n]", c.telefone);

    limparBuffer(); // limpa ENTER deixado pelo scanf

    printf("E-mail (opcional, pressione ENTER para pular): ");
    fgets(c.email, sizeof(c.email), stdin);

    if (c.email[0] == '\n') {
        strcpy(c.email, "Não informado");
    } else {
        c.email[strcspn(c.email, "\n")] = '\0'; // remove \n
    }

    clientes[qtdClientes++] = c;
    printf("Cliente cadastrado!\n");
}

void consultarCliente() {
    int id;
    printf("ID do cliente: ");
    scanf("%d", &id);
    for (int i = 0; i < qtdClientes; i++) {
        if (clientes[i].id == id) {
            printf("Cliente %d | Nome: %s | Telefone: %s | Email: %s\n",
                   clientes[i].id, clientes[i].nome, clientes[i].telefone, clientes[i].email);
            return;
        }
    }
    printf("Cliente não encontrado!\n");
}

void editarCliente() {
    int id;
    printf("ID do cliente a editar: ");
    scanf("%d", &id);

    for (int i = 0; i < qtdClientes; i++) {
        if (clientes[i].id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", clientes[i].nome);

            printf("Novo telefone: ");
            scanf(" %[^\n]", clientes[i].telefone);

            limparBuffer();

            printf("Novo e-mail (opcional, pressione ENTER para pular): ");
            fgets(clientes[i].email, sizeof(clientes[i].email), stdin);
            if (clientes[i].email[0] == '\n') {
                strcpy(clientes[i].email, "Não informado");
            } else {
                clientes[i].email[strcspn(clientes[i].email, "\n")] = '\0';
            }

            printf("Cliente atualizado!\n");
            return;
        }
    }
    printf("Cliente não encontrado!\n");
}

void listarClientes() {
    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < qtdClientes; i++) {
        printf("ID: %d | Nome: %s | Telefone: %s | Email: %s\n",
               clientes[i].id, clientes[i].nome, clientes[i].telefone, clientes[i].email);
    }
    if (qtdClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
    }
}
void historicoCompras(int clienteId) {
    Cliente *cliente = NULL;
    for (int i = 0; i < qtdClientes; i++) {
        if (clientes[i].id == clienteId) {
            cliente = &clientes[i];
            break;
        }
    }
    if (!cliente) {
        printf("Cliente não encontrado!\n");
        return;
    }

    printf("\n=== Histórico de Compras ===\n");
    printf("Cliente: %s | Telefone: %s | Email: %s\n",
           cliente->nome, cliente->telefone, cliente->email);

    float totalGasto = 0;
    int countPIX = 0, countDebito = 0, countCredito = 0, countDinheiro = 0;

    for (int i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].clienteId == clienteId) {
            printf("\nPedido Nº %d | Data/Hora: %s | Status: %s\n",
                   pedidos[i].id, pedidos[i].dataHora, pedidos[i].status);

            for (int j = 0; j < pedidos[i].qtdItens; j++) {
                int prodId = pedidos[i].itens[j].produtoId;
                Produto *prod = NULL;
                for (int k = 0; k < qtdProdutos; k++) {
                    if (produtos[k].id == prodId) {
                        prod = &produtos[k];
                        break;
                    }
                }
                if (prod) {
                    printf(" - %s | Qtd: %d | Subtotal: R$ %.2f\n",
                           prod->nome,
                           pedidos[i].itens[j].quantidade,
                           pedidos[i].itens[j].subtotal);
                }
            }

            // Buscar pagamento do pedido
            for (int p = 0; p < qtdPagamentos; p++) {
                if (pagamentos[p].pedidoId == pedidos[i].id) {
                    printf("Pagamento: R$ %.2f | Método: %s\n",
                           pagamentos[p].valor, pagamentos[p].metodo);
                    totalGasto += pagamentos[p].valor;

                    if (strcmp(pagamentos[p].metodo, "PIX") == 0) countPIX++;
                    else if (strcmp(pagamentos[p].metodo, "Debito") == 0) countDebito++;
                    else if (strcmp(pagamentos[p].metodo, "Credito") == 0) countCredito++;
                    else if (strcmp(pagamentos[p].metodo, "Dinheiro") == 0) countDinheiro++;
                }
            }
        }
    }

    printf("\nTotal gasto pelo cliente: R$ %.2f\n", totalGasto);

    // Modalidade preferida
    printf("Modalidade de pagamento mais usada: ");
    if (countPIX >= countDebito && countPIX >= countCredito && countPIX >= countDinheiro)
        printf("PIX (%d vezes)\n", countPIX);
    else if (countDebito >= countPIX && countDebito >= countCredito && countDebito >= countDinheiro)
        printf("Débito (%d vezes)\n", countDebito);
    else if (countCredito >= countPIX && countCredito >= countDebito && countCredito >= countDinheiro)
        printf("Crédito (%d vezes)\n", countCredito);
    else
        printf("Dinheiro (%d vezes)\n", countDinheiro);

    printf("====================================\n\n");
}

void menuClientes() {
    int op;
    do {
        printf("\n--- Clientes ---\n");
        printf("1. Cadastrar\n2. Consultar\n3. Editar\n4. Listar\n5. Histórico\n0. Voltar\nEscolha: ");
        scanf("%d",&op);
        switch(op) {
            case 1: cadastrarCliente(); break;
            case 2: consultarCliente(); break;
            case 3: editarCliente(); break;
            case 4: listarClientes(); break;
            case 5: historicoCompras(1); break; // exemplo
        }
    } while(op!=0);
}
