#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

typedef struct{
     unsigned long id;
     char nome[100];
     char cpf[12];
     char email[50];
     char telefone[15];
     char password[20];
}Vendedor;

void cadastroVendedor(FILE *);
void alteracaoVendedor(FILE *);
void consultaVendedor(FILE *);
void listagemVendedor(FILE *);
int pesquisaArqIDVend(FILE *, int);
int pesquisaArqCPFVend(FILE *, char[12]);
int pesquisaArqPrefVend(FILE *, char[3]);
void printarConsultaVend(FILE *, int);
int gerarIDVend(FILE *);

#endif // VENDEDOR_H_INCLUDED
