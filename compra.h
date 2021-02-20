#ifndef COMPRA_H_INCLUDED
#define COMPRA_H_INCLUDED

//Compra de produtos do fornecedor

typedef struct{
    unsigned long id;
    unsigned long idFornecedor;
    char dataCompra[11];
    float valorTotal;
}NotaCompra;

typedef struct{
    unsigned long id;
    unsigned long idProduto;
    unsigned long idNotaCompra;
    unsigned int quantidade;
    float ValorUnitario;
}ItemNotaCompra;

typedef struct{
    unsigned long idProduto;
    unsigned int quantidade;
    float valorUnitario;
}CarrinhoCompra;

int compra(FILE *, FILE *, FILE *, FILE *);
int verificaFornecedor(FILE *, int);
int gerarIDNotaCompra(FILE *);
int gerarIDItemNotaCompra(FILE *);


#endif // COMPRA_H_INCLUDED
