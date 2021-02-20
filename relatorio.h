#ifndef RELATORIO_H_INCLUDED
#define RELATORIO_H_INCLUDED

typedef struct{
    unsigned long idProduto;
    char dataAlteracao[11];
    float Valor;
}HistoricoPreco;

void relatorioNFVenda(FILE *, FILE *, FILE*);
void relatorioNFCompra(FILE *, FILE *, FILE *);
void relatorioCliente(FILE *, FILE *, FILE *);
void relatorioNFVendedore(FILE *, FILE *);
void relatorioHistorico(FILE *, FILE *);

int pesquisaArqIDNota(FILE *, int);
void printarRelatorioNota(FILE *, int);

int pesquisaArqIDNotaComp(FILE *, int);
void printarRelatorioNotaComp(FILE *, int);

int pesquisaArqIDNotaCli(FILE *, int);
int comparaData(FILE *, char[11]);
void printarRelatorioNotaCli(FILE *, int);

int pesquisaArqIDNotaVend(FILE *, int);
int comparaDia(FILE *, int);
int comparaMes(FILE *, int);

int pesquisaArqIDProdHP(FILE *, int);
void printarRelatorioHP(FILE *, int);

#endif // RELATORIO_H_INCLUDED