cmake_minimum_required(VERSION 3.10)

project(C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C
        main.c
        clientes.c
        comprovante.c
        estoque.c
        pagamentos.c
        pedidos.c
        produtos.c
        relatorios.c
        salvar.c
        salvar.h
)
