#ifndef VENDA_H_INCLUDED
#define VENDA_H_INCLUDED

//Venda de produtos para o cliente

typedef struct{
    unsigned long id;
    unsigned long idCliente;
    unsigned long idVendedor;
    char dataCompra[11];
    float valorTotal;
}NotaFiscal;

typedef struct{
    unsigned long id;
    unsigned long idNotaFiscal;
    unsigned long idProduto;
    float valorVenda;
    unsigned int quantidade;
}ItemNotaFiscal;

typedef struct{
    unsigned long idProduto;
    unsigned int quantidadeVendida;
    float valorVenda;
}Carrinho;

void venda(FILE *, FILE *, FILE *, FILE *, FILE *);
int verificaVendedor(FILE *, char[12], char[20]);
int gerarIDNota(FILE *);
int gerarIDItemNotaFiscal(FILE *);




#endif // NOTAFISCAL_H_INCLUDED
