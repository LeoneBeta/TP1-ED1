#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100];
    unsigned int quantidadeEstoque;
    float precoUnitario;
}Produto;

void cadastroProduto(FILE *);
void alteracaoProduto(FILE *, FILE *);
int atualizaEstqProd(FILE *, int, int, int);
void consultaProduto(FILE *);
void listagemProduto(FILE *);
int pesquisaArqIDProd(FILE *, int);
int pesquisaArqPrefProd(FILE *, char[3]);
void printarConsultaProd(FILE *, int);
int gerarIDProd(FILE *);

#endif // PRODUTO_H_INCLUDED
