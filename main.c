#include <stdio.h>
#include <stdlib.h>

#include "produtos.h"
#include "clientes.h"
#include "pedidos.h"
#include "pagamentos.h"
#include "relatorios.h"
#include "comprovante.h"
#include "estoque.h"
#include "salvar.h"

int main() {
    carregarDados();

    int opcao;
    int pedidoId;
    do {
        printf("\n=== Sistema Principal ===\n");
        printf("1. Produtos\n");
        printf("2. Clientes\n");
        printf("3. Pedidos\n");
        printf("4. Pagamentos\n");
        printf("5. Relatório de Vendas\n");
        printf("6. Gerar Comprovante\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d",&opcao);

        switch(opcao) {
            system("cls");
            case 1: menuProdutos(); break;
            case 2: menuClientes(); break;   // <-- corrigido
            case 3: menuPedidos(); break;    // idem para pedidos
            case 4: menuPagamentos(); break; // idem para pagamentos
            case 5: consultarVendas(); break;
            case 6:
                listarPedidos();
                printf("Informe o número do pedido: ");
                scanf("%d", &pedidoId);
                gerarComprovante(pedidoId);
                break; // exemplo
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida!\n");
        }
        salvarDados();
    } while(opcao!=0);

    salvarDados();
    return 0;
}
