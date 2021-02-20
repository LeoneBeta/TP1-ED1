#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
}Cliente;

void cadastroCliente(FILE *);
void alteracaoCliente(FILE *);
void consultaCliente(FILE *); //Consulta feita por id, cpf e/ou prefixo do nome.
void listagemCliente(FILE *);
int pesquisaArqIDCli(FILE *, int);
int pesquisaArqCPFCli(FILE *, char[12]);
int pesquisaArqPrefCli(FILE *, char[3]);
void printarConsultaCli(FILE *, int);
int gerarIDCli(FILE *);

#endif // CLIENTE_H_INCLUDED
