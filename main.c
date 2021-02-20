#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "cliente.h"
#include "compra.h"
#include "fornecedor.h"
#include "venda.h"
#include "produto.h"
#include "vendedor.h"
#include "relatorio.h"
#include "utilitarios.h"

int main(){
    setlocale(LC_ALL,"portuguese");
    char menu[1], submenu[1];
    FILE *ACli, *AVend, *AForn, *ANota, *AINota, *AProd, *ANotaComp, *AINotaComp, *AHistPre;
    abrirArquivos(&ACli, &AVend, &AForn, &ANota, &AINota, &AProd, &ANotaComp, &AINotaComp, &AHistPre);

    do{
        
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~~~~~ Farmaco-Dev ~~~~~~~~~");
        printf("\n~~~~~1 - Efetuar Venda~~~~~~~~~");
        printf("\n~~~~~2 - Comprar Mercadorias~~~");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~3 - Cadastro~~~~~~~~~~~~~~");
        printf("\n~~~~~4 - Consulta~~~~~~~~~~~~~~");
        printf("\n~~~~~5 - Listagem~~~~~~~~~~~~~~");
        printf("\n~~~~~6 - Manutenção~~~~~~~~~~~~");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~7 - Relatório ~~~~~~~~~~~~");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~0 - Sair~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        scanf("%s",&menu[0]);

        if(menu[0]=='1'){venda(AVend,ACli,AProd,ANota,AINota);}

        if(menu[0]=='2'){compra(AProd,AForn,ANotaComp,AINotaComp);}

        if(menu[0]=='3'){
            system("clear");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~ Cadastro ~~~~~~~~~~");
            printf("\n~~~~~1 - Cliente~~~~~~~~~~~~~~~");
            printf("\n~~~~~2 - Vendedor~~~~~~~~~~~~~~");
            printf("\n~~~~~3 - Fornecedor~~~~~~~~~~~~");
            printf("\n~~~~~4 - Produto~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~ Selecione para Cadastro ~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~0 - Sair~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            scanf("%s",&submenu[0]);

            if(submenu[0]=='1'){cadastroCliente(ACli);}
            if(submenu[0]=='2'){cadastroVendedor(AVend);}
            if(submenu[0]=='3'){cadastroFornecedor(AForn);}
            if(submenu[0]=='4'){cadastroProduto(AProd);}
        }

        if(menu[0]=='4'){
            system("clear");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~ Consulta ~~~~~~~~~~");
            printf("\n~~~~~1 - Cliente~~~~~~~~~~~~~~~");
            printf("\n~~~~~2 - Vendedor~~~~~~~~~~~~~~");
            printf("\n~~~~~3 - Fornecedor~~~~~~~~~~~~");
            printf("\n~~~~~4 - Produto~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~ Selecione para Consulta ~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~0 - Sair~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            scanf("%s",&submenu[0]);

            if(submenu[0]=='1'){consultaCliente(ACli);}
            if(submenu[0]=='2'){consultaVendedor(AVend);}
            if(submenu[0]=='3'){consultaFornecedor(AForn);}
            if(submenu[0]=='4'){consultaProduto(AProd);}
        }

        if(menu[0]=='5'){
            system("clear");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~ Listagem ~~~~~~~~~~");
            printf("\n~~~~~1 - Cliente~~~~~~~~~~~~~~~");
            printf("\n~~~~~2 - Vendedor~~~~~~~~~~~~~~");
            printf("\n~~~~~3 - Fornecedor~~~~~~~~~~~~");
            printf("\n~~~~~4 - Produto~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~ Selecione para Listagem ~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~0 - Sair~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            scanf("%s",&submenu[0]);

            if(submenu[0]=='1'){listagemCliente(ACli);}
            if(submenu[0]=='2'){listagemVendedor(AVend);}
            if(submenu[0]=='3'){listagemFornecedor(AForn);}
            if(submenu[0]=='4'){listagemProduto(AProd);}
        }

        if(menu[0]=='6'){
            system("clear");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~ Manutenção ~~~~~~~~~~");
            printf("\n~~~~~1 - Cliente~~~~~~~~~~~~~~~");
            printf("\n~~~~~2 - Vendedor~~~~~~~~~~~~~~");
            printf("\n~~~~~3 - Fornecedor~~~~~~~~~~~~");
            printf("\n~~~~~4 - Produto~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~ Selecione para manutenção ~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~0 - Sair~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            scanf("%s",&submenu[0]);

            if(submenu[0]=='1'){alteracaoCliente(ACli);}
            if(submenu[0]=='2'){alteracaoVendedor(AVend);}
            if(submenu[0]=='3'){alteracaoFornecedor(AForn);}
            if(submenu[0]=='4'){alteracaoProduto(AProd,AHistPre);}
        }
        
        if(menu[0]=='7'){
            system("clear");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~ Relatório ~~~~~~~~~~");
            printf("\n~~~~~1 - Nota Fiscal Vendas ~~~");
            printf("\n~~~~~2 - Nota Fiscal Compras ~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~3 - Relatório Cliente ~~~~");
            printf("\n~~~~~4 - Relatório Vendedor ~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~5 - Relatório Produtos ~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~0 - Sair~~~~~~~~~~~~~~~~~~");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            scanf("%s",&submenu[0]);
            
            if(submenu[0]=='1'){relatorioNFVenda(ANota,AProd,AINota);}
            if(submenu[0]=='2'){relatorioNFCompra(ANotaComp,AProd,AINotaComp);}
            if(submenu[0]=='3'){relatorioCliente(ANota,AProd,AINota);}
            if(submenu[0]=='4'){relatorioNFVendedore(ANota,AProd);}
            if(submenu[0]=='5'){relatorioHistorico(AHistPre,AProd);}
        }

    }while(menu[0] != '0');

    fecharArquivos(&ACli, &AVend, &AForn, &ANota, &AINota, &AProd, &ANotaComp, &AINotaComp, &AHistPre);
    return 0;
}
