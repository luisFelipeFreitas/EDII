#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Conta {
    int cod;
    int codAgencia;
    double Saldo;
} Conta;

// Imprime funcionario
void imprime(Conta *conta);

// Cria funcionario. Lembrar de usar free(funcionario)
Conta *cont(int cod, int codAgencia, double saldo);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(Conta *conta, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
Conta *le(FILE *in);

// Retorna tamanho do funcionario em bytes
int tamanho();

#endif