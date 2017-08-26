#include <stdio.h>
#include <stdlib.h>
#include "conta.h"

void insere_funcionarios(FILE *out,int x) {
    //printf("Inserindo 5 funcionários no arquivo...");
    int counter=0;
    int cod;
    int codAgencia;
    double saldo;
    fseek(out, tamanho() * x, SEEK_SET);
    
    printf("Digite o codigo da conta \n");
    scanf("%d",&cod);
    printf("Digite o codigo da agencia \n");
    scanf("%d",&codAgencia);
    printf("Digite o saldo da conta \n");
    scanf("%lf",&saldo);
    Conta *f = cont(cod, codAgencia,saldo);
    salva(f,out);
    free(f);
    counter++;
    
}

void le_funcionarios(FILE *in) {
    printf("\n\nLendo contas do arquivo...\n\n");
    rewind(in);
    Conta *f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

void le_segundo_funcionario(FILE *in) {
    printf("\n\nLendo segunda conta do arquivo...\n\n");
    //tamanho() indica quantos bytes vamos pular, o que aqui é igual ao tamanho de um registro
    //(vamos pular o primeiro e nos posicionar no início do segundo)
    //** ATENÇÃO: não usar sizeof(Conta), pois ele pode retornar valor maior que o tamanho ocupado em disco,
    //            devido a alinhamento automático (ver https://en.wikipedia.org/wiki/Data_structure_alignment))
    //SEEK_SET indica o início do arquivo
    //ao final, o cursor estará posicionado em 0 + tamanho() +1
    fseek(in, tamanho(), SEEK_SET);
    Conta *f = le(in);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
}

void adiciona_funcionario(FILE *in) {
    printf("\n\nAdicionando funcionário no final do arquivo...\n\n");
    //pula 5 registros para posicionar no início do final do arquivo
    fseek(in, tamanho() * 5, SEEK_SET);
    Conta *f = cont(6,3123,400.00);
    salva(f, in);
    free(f);

    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 5, SEEK_SET);
    Conta *f6 = le(in);
    if (f6 != NULL) {
        imprime(f6);
        free(f6);
    }
}

void sobrescreve_quarto_funcionario(FILE *in) {
    printf("\n\nSobrescrevendo quarto funcionário do arquivo...\n\n");
    //pula primeiros 3 registros para posicionar no início do quarto registro
    fseek(in, tamanho() * 3, SEEK_SET);
    Conta *f4 = cont(7,3123,400.00);
    salva(f4, in);
    free(f4);

    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanho() * 3, SEEK_SET);
    Conta *f = le(in);
    if (f != NULL) {
        imprime(f);
        free(f);
    }
}

int main(int argc, char** argv) {
    //declara ponteiro para arquivo
    FILE *out;
    //abre arquivo
    if ((out = fopen("funcionario.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        int state=0;
	int nro=0;
	while(state!=4){
	    printf("Digite 1 caso queira inserir, digite 2 caso queira ler e digite 4 caso queira sair!: ");
	    scanf("%d",&state);
	    if(state==1){
	    	insere_funcionarios(out,nro);
		nro++;
	    }
	    
	    if(state==2)le_funcionarios(out);
	}
        fclose(out);
	return 0;    
    }
}

