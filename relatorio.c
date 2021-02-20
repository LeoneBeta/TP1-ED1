#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorio.h"
#include "venda.h"
#include "produto.h"
#include "compra.h"
#include "cliente.h"
#include "utilitarios.h"

//Dados de uma Venda
void relatorioNFVenda(FILE *ANota, FILE *AProd, FILE *AINota){

    int sair, localNota, n, j;
    unsigned long idNota;

    ItemNotaFiscal inf;
    Produto prod;


    do{
        printf("\nForneça o ID da Nota Fiscal: ");
        scanf("%lu",&idNota);

        fseek(ANota,0,SEEK_SET);
        localNota = pesquisaArqIDNota(ANota,idNota);
        if(localNota != -1){
            printarRelatorioNota(ANota,localNota);

            /*Faz uma busca vinculando os IDs das Notas Fiscais com os Itens Nota, assim vinculando os
            IDs dos produtos dos Itens Notas, com os IDs dos produtos no proprio arquivo*/
            n=0;
            fseek(AINota,0,SEEK_SET);
            while(fread(&inf,n*sizeof(ItemNotaFiscal),1,AINota)){
                if(inf.idNotaFiscal == idNota){
                    j=0;
                    while(fread(&prod,j*sizeof(Produto),1,AProd)){
                        if(inf.idProduto == prod.id)
                            printf("\nNome Produto: %s",prod.nome);
                        j++;
                    }
                }
                n++;
            }
        }else
            printf("\nNenhuma Nota Fiscal no arquivo");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nRelatório de outra Nota Fiscal? ");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while( sair != 1);
}
//Dados de uma Compra
void relatorioNFCompra(FILE *ANotaComp, FILE *AProd, FILE *AINotaComp){

    int sair, local, n, j;
    unsigned long idNota;

    ItemNotaCompra inc;
    Produto prod;

    do{
        printf("\nForneça o ID da Compra: ");
        scanf("%lu",&idNota);

        fseek(ANotaComp,0,SEEK_SET);
        local = pesquisaArqIDNotaComp(ANotaComp,idNota);
        if(local != -1){
            printarRelatorioNotaComp(ANotaComp,local);

            /*Faz uma busca vinculando os IDs das Notas de Compra com os Itens Nota Compra, assim vinculando os
            IDs dos produtos dos Itens Notas Compra, com os IDs dos produtos no proprio arquivo*/
            n=0;
            fseek(AINotaComp,0,SEEK_SET);
            while(fread(&inc,n*sizeof(ItemNotaCompra),1,AINotaComp)){
                if(inc.idNotaCompra == idNota){
                    j=0;
                    while(fread(&prod,j*sizeof(Produto),1,AProd)){
                        if(inc.idProduto == prod.id)
                            printf("\nNome Produto: %s",prod.nome);
                        j++;
                    }
                }
                n++;
            }
        }else
            printf("\nNenhuma Nota Fiscal no arquivo");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nRelatório de outra Nota de Compra? ");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while( sair != 1);
}
//Dados referente a um Cliente
void relatorioCliente(FILE *ANota, FILE *AProd, FILE *AINota){

    int sair, localCli, validaData, n, j;
    unsigned long idCli;
    char data[11];

    ItemNotaFiscal inf;
    Produto prod;


    do{
        printf("\nForneça o ID do cliente: ");
        scanf("%lu",&idCli);

        fseek(ANota,0,SEEK_SET);
        localCli = pesquisaArqIDNotaCli(ANota,idCli);
        if(localCli != -1){
            setbuf(stdin,NULL);
            printf("\nForneça uma data - dd/mm/aaaa:");
            fgets(data,11,stdin);
            retiraEnter(data);
            validaData = comparaData(ANota,data);
            if(validaData){
                printarRelatorioNota(ANota,localCli);

                /*Faz uma busca vinculando os IDs das Notas Fiscais com os Itens Nota, assim vinculando os
                IDs dos produtos dos Itens Notas, com os IDs dos produtos no proprio arquivo*/
                n=0;
                fseek(AINota,0,SEEK_SET);
                while(fread(&inf,n*sizeof(ItemNotaFiscal),1,AINota)){
                    if(inf.idNotaFiscal == idCli){
                        j=0;
                        while(fread(&prod,j*sizeof(Produto),1,AProd)){
                            if(inf.idProduto == prod.id)
                                printf("\nNome Produto: %s",prod.nome);
                            j++;
                        }
                    }
                    n++;
                }
            }else
                printf("\nNota não encontrada com essa Data");
        }else
            printf("\nNenhuma Nota Fiscal no arquivo");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nRelatório de outra Nota Fiscal? ");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while( sair != 1);
}
//Dados referente a um Vendedor em um Dia ou Mes fornecido
void relatorioNFVendedore(FILE *ANota, FILE *AProd){

    int sair, idVend, menuData, dia, mes, localVend, posicaoData;
    int n, j;
    int diaInt,mesInt;
    char diaChar[2], mesChar[2];

    NotaFiscal consultaVend, consultaData, printar;

    do{
        printf("\nForneça o ID do Vendedor: ");
        scanf("%d",&idVend);

        localVend = pesquisaArqIDNotaVend(ANota,idVend);

        if(localVend != -1){
            printf("\nBusca por...");
            printf("\n0 - Dia ... 1 - Mês");
            scanf("%d",&menuData);

            //Pesquisa por Dia
            /*Faz uma busca pelo ID do vendedor, viculando com uma busca por Dia fornecido, armazenando
            a ultima posição pesquisada do ID na variável "n", e a ultima posição pesquisada por Dia na
            variável "j"*/
            if(menuData ==0){
                printf("\nForneça o Dia para busca: ");
                scanf("%d",&dia);
                posicaoData = comparaDia(ANota,dia);
                if(posicaoData > 0){
                    n=0;
                    fseek(ANota,n*sizeof(NotaFiscal),SEEK_SET);
                    while(fread(&consultaVend,n*sizeof(NotaFiscal),1,ANota)){
                        if(consultaVend.idVendedor == idVend){
                            j=0;
                            fseek(ANota,j*sizeof(NotaFiscal),SEEK_SET);
                            while(fread(&consultaData,j*sizeof(NotaFiscal),1,ANota)){
                                diaChar[0] = consultaData.dataCompra[0];
                                diaChar[1] = consultaData.dataCompra[1];
                                diaInt = atoi(diaChar);
                                if(diaInt == dia){
                                    printf("\n~~~ Relatório Vendedor no Dia ~~~");
                                    printf("\nID: %lu",printar.id);
                                    printf("\nID Cliente: %lu",printar.idCliente);
                                    printf("\nID Vendedor: %lu", printar.idVendedor);
                                    printf("\nData da Venda: %s",printar.dataCompra);
                                    printf("\nValor: %f",printar.valorTotal);
                                    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                                }
                                fseek(ANota,j*sizeof(NotaFiscal),SEEK_SET);
                            }
                        }
                        n++;
                        fseek(ANota,n*sizeof(NotaFiscal),SEEK_SET);
                    }
                }else
                    printf("\nNenhuma Nota neste Dia");

            //Pesquisa por Mês
            /*Mesmo esquema de Busca por dia, alterando apenas o vinculo do ID com Dia, para ID com Mes*/
            }else{
                printf("\nForneça o Mês para busca: ");
                scanf("%d",&mes);
                posicaoData = comparaMes(ANota,mes);
                if(posicaoData > 0){
                    n=0;
                    fseek(ANota,n*sizeof(NotaFiscal),SEEK_SET);
                    while(fread(&consultaVend,sizeof(NotaFiscal),1,ANota)){
                        if(consultaVend.idVendedor == idVend){
                            j=0;
                            fseek(ANota,j*sizeof(NotaFiscal),SEEK_SET);
                            while(fread(&consultaData,sizeof(NotaFiscal),1,ANota)){
                                mesChar[0] = consultaData.dataCompra[3];
                                mesChar[1] = consultaData.dataCompra[4];
                                mesInt = atoi(mesChar);
                                if(mesInt == dia){
                                    printf("\n~~~ Relatório Vendedor no Mês ~~~");
                                    printf("\nID: %lu",printar.id);
                                    printf("\nID Cliente: %lu",printar.idCliente);
                                    printf("\nID Vendedor: %lu", printar.idVendedor);
                                    printf("\nData da Venda: %s",printar.dataCompra);
                                    printf("\nValor: %f",printar.valorTotal);
                                    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                                }
                                fseek(ANota,j*sizeof(NotaFiscal),SEEK_SET);
                            }
                        }
                        n++;
                        fseek(ANota,n*sizeof(NotaFiscal),SEEK_SET);
                    }
                }else
                    printf("\nNenhuma Nota neste Mês");
            }
        }else
            printf("\nID de Vendedor não encontrado");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nRelatório de outro Vendedor? ");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair != 1);
}
//Dados de historico de preço de um produto
void relatorioHistorico(FILE *AHistPre, FILE *AProd){

    int sair, idProd, local;

    do{
        printf("\nForneça o ID do produto");
        scanf("%d",&idProd);

        local = pesquisaArqIDProdHP(AHistPre, idProd);
        if(local != -1)
            printarRelatorioHP(AHistPre,local);
        else
            printf("\nID não encontrado");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nRelatório de outro Produto? ");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair != 1);
}


//Pesquisa o ID da Nota Fiscal no arquivo
int pesquisaArqIDNota(FILE *ANota, int idNota){
    int posicao = 0;
    NotaFiscal consulta;
    fseek(ANota,0,SEEK_SET);
        while(fread(&consulta,sizeof(NotaFiscal),1,ANota) == 1){
            if(consulta.id == idNota)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Printa o Relatorio da Nota Fiscal
void printarRelatorioNota(FILE *ANota, int local){
    NotaFiscal consulta;
    fseek(ANota,local*sizeof(NotaFiscal),SEEK_SET);
    fread(&consulta,sizeof(NotaFiscal),1,ANota);
    printf("\n~~~~~ Relatorio Nota Fiscal ~~~~~");
    printf("\nID: %lu",consulta.id);
    printf("\nID Cliente: %lu",consulta.idCliente);
    printf("\nID Vendedor: %lu", consulta.idVendedor);
    printf("\nData da Venda: %s",consulta.dataCompra);
    printf("\nValor: %f",consulta.valorTotal);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


//Pesquisa o ID da Nota de Compra no arquivo
int pesquisaArqIDNotaComp(FILE *ANotaComp, int idNota){
    int posicao = 0;
    NotaFiscal consulta;
    fseek(ANotaComp,0,SEEK_SET);
        while(fread(&consulta,sizeof(NotaFiscal),1,ANotaComp) == 1){
            if(consulta.id == idNota)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Printa o Relatorio da Nota de Compra
void printarRelatorioNotaComp(FILE *ANotaComp, int local){
    NotaCompra consulta;
    fseek(ANotaComp,local*sizeof(NotaFiscal),SEEK_SET);
    fread(&consulta,sizeof(NotaFiscal),1,ANotaComp);
    printf("\n~~~~~ Relatorio Nota Compra ~~~~~");
    printf("\nID: %lu",consulta.id);
    printf("\nID Cliente: %lu",consulta.idFornecedor);
    printf("\nData da Venda: %s",consulta.dataCompra);
    printf("\nValor: %f",consulta.valorTotal);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


//Procura no arquivo de Notas Fiscais o ID do Cliente fornecido
int pesquisaArqIDNotaCli(FILE *ANota, int idCli){
    int posicao = 0;
    NotaFiscal consulta;
    fseek(ANota,0,SEEK_SET);
        while(fread(&consulta,sizeof(NotaFiscal),1,ANota) == 1){
            if(consulta.idCliente == idCli)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Compara a data fornecida com a da nota
int comparaData(FILE *ANota, char data[11]){
    int n = 1;
    NotaFiscal nf;
    while(fread(&nf,n*sizeof(NotaFiscal),1,ANota)){
        if(strcmp(nf.dataCompra,data))
            return 1;
        n++;
    }
    return 0;
}
//Printa o Relatorio das notas do Cliente fornecido
void printarRelatorioNotaCli(FILE *ANota, int local){
    NotaFiscal consulta;
    fseek(ANota,local*sizeof(NotaFiscal),SEEK_SET);
    fread(&consulta,sizeof(NotaFiscal),1,ANota);
    printf("\n~~~~~ Relatorio do Cliente ~~~~~");
    printf("\nID: %lu",consulta.id);
    printf("\nID Cliente: %lu",consulta.idCliente);
    printf("\nID Vendedor: %lu", consulta.idVendedor);
    printf("\nData da Venda: %s",consulta.dataCompra);
    printf("\nValor: %f",consulta.valorTotal);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


//Pesquisa o ID do Vendedor no arquivo NotaFiscal
int pesquisaArqIDNotaVend(FILE *ANota, int idVend){
    int posicao = 0;
    NotaFiscal consulta;
    fseek(ANota,0,SEEK_SET);
        while(fread(&consulta,sizeof(NotaFiscal),1,ANota) == 1){
            if(consulta.idVendedor == idVend)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Compara o dia fornecido com as datas nas Notas Fiscais
int comparaDia(FILE *ANota, int dia){
    int n = 1, diaInt;
    char diaChar[2];
    NotaFiscal nf;
    while(fread(&nf,n*sizeof(NotaFiscal),1,ANota)){
        diaChar[0] = nf.dataCompra[0];
        diaChar[1] = nf.dataCompra[1];
        diaInt = atoi(diaChar);
        if(diaInt == dia)
            return n;
        n++;
    }
    return 0;
}
//Compara o mês fornecido com as datas nas Notas Fiscais
int comparaMes(FILE *ANota, int mes){
    int n = 1, mesInt;
    char mesChar[2];
    NotaFiscal nf;
    while(fread(&nf,n*sizeof(NotaFiscal),1,ANota)){
        mesChar[0] = nf.dataCompra[3];
        mesChar[1] = nf.dataCompra[4];
        mesInt = atoi(mesChar);
        if(mesInt == mes)
            return n;
        n++;
    }
    return 0;
}


//Pesquisa o ID do Produto no arquivo HistoricoPreco
int pesquisaArqIDProdHP(FILE *AHistPre, int idProd){
    int posicao = 0;
    HistoricoPreco consulta;
    fseek(AHistPre,0,SEEK_SET);
        while(fread(&consulta,sizeof(HistoricoPreco),1,AHistPre) == 1){
            if(consulta.idProduto == idProd)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Printa o Relatório do Historico de Preços de um determinado produto
void printarRelatorioHP(FILE *AHistPre, int local){
    HistoricoPreco consulta;
    fseek(AHistPre,local*sizeof(NotaFiscal),SEEK_SET);
    fread(&consulta,sizeof(NotaFiscal),1,AHistPre);
    printf("\n~~~~~ Relatorio Nota Fiscal ~~~~~");
    printf("\nID: %lu",consulta.idProduto);
    printf("\nID Valor: %f", consulta.Valor);
    printf("\nData de Alteração: %s",consulta.dataAlteracao);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
