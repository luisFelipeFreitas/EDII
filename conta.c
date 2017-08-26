#include "conta.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

// Imprime Cont
void imprime(Conta *Cont) {
    printf("**********************************************");
    printf("\nCódigo da conta ");
    printf("%d", Cont->cod);
    printf("\nCodigo da agencia ");
    printf("%d", Cont->codAgencia);
    printf("\nSaldo ");
    printf("%4.2f", Cont->Saldo);
    printf("\n**********************************************\n");
}

// Cria Cont. Lembrar de usar free(Conta)
Conta *cont(int cod, int codAgencia, double saldo) {
    Conta *Cont = (Conta *) malloc(sizeof(Conta));
    //inicializa espaço de memória com ZEROS
    if (Cont) memset(Cont, 0, sizeof(Conta));
    //copia valores para os campos de Cont
    Cont->cod = cod;
    Cont->codAgencia = codAgencia;
    Cont->Saldo = saldo;
    return Cont;
}

// Salva Cont no arquivo out, na posicao atual do cursor
void salva(Conta *Conta, FILE *out) {
    fwrite(&Conta->cod, sizeof(int), 1, out);
    //Conta->nome ao invés de &Cont->nome, pois string já é ponteiro
    fwrite(&Conta->codAgencia, sizeof(int), 1, out);
    fwrite(&Conta->Saldo, sizeof(double), 1, out);
}

// Le um Cont do arquivo in na posicao atual do cursor
// Retorna um ponteiro para Cont lido do arquivo
Conta *le(FILE *in) {
    Conta *Cont = (Conta *) malloc(sizeof(Conta));
    if (0 >= fread(&Cont->cod, sizeof(int), 1, in)) {
        free(Cont);
        return NULL;
    }
    
    //Conta->nome ao invés de &Cont->nome, pois string já é ponteiro
    fread(&Cont->codAgencia, sizeof(int), 1, in);
    fread(&Cont->Saldo, sizeof(double), 1, in);
    return Cont;
}

// Retorna tamanho do Cont em bytes
int tamanho() {
    return sizeof(int) + sizeof(int) + sizeof(double);
}