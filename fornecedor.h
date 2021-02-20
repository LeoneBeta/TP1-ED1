#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

typedef struct{
    unsigned long id;
    char CNPJ[15];
    char nome[100];
    char email[50];
    char telefone[15];
}Fornecedor;

void cadastroFornecedor(FILE *);
void alteracaoFornecedor(FILE *);
void consultaFornecedor(FILE *);
void listagemFornecedor(FILE *);
int pesquisaArqIDForn(FILE *, int);
int pesquisaArqCNPJForn(FILE *, char[15]);
int pesquisaArqPrefForn(FILE *, char[3]);
void printarConsultaForn(FILE *, int);
int gerarIDForn(FILE *);

#endif // FORNECEDOR_H_INCLUDED
