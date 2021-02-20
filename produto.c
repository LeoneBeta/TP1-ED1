#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"
#include "utilitarios.h"
#include "relatorio.h"

//Cadastro de novos Produtos
void cadastroProduto(FILE *AProd){

    int sair = 0;
    Produto novo;

    do{
        system("clear");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        novo.id = gerarIDProd(AProd);
        setbuf(stdin,NULL);
        printf("\nNome do Produto: ");
        fgets(novo.nome,100,stdin);
        retiraEnter(novo.nome);
        conversorTexto(novo.nome);

        setbuf(stdin,NULL);
        printf("\nQuantidade em Estoque: ");
        scanf("%d",&novo.quantidadeEstoque);
        printf("\nPreço Unitário: ");
        scanf("%f",&novo.precoUnitario);
        setbuf(stdin,NULL);

        fseek(AProd,0,SEEK_END);
        fwrite(&novo,sizeof(Produto),1,AProd);

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Cadastrar outro produto?");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair != 1);
}
//Alteração de Produto
void alteracaoProduto(FILE *AProd, FILE *AHistPre){

    int id, sair, local, menu, submenu,
        idProd, sinal, posicao, n;
    float porcentagem;

    struct tm *info;                                //Data
    time_t rawtime;                                 //Data

    Produto alt;
    HistoricoPreco hp;

    do{
        system("clear");
        printf("\nAlteração de Produto");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n0-Produto ... 1-Valor\n");
        scanf("%d",&menu);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        switch(menu){
        //Altera todos os dados do Produto
        case 0:
            do{
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o ID do Produto: ");
                scanf("%d",&id);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

                fseek(AProd,0,SEEK_SET);
                local = pesquisaArqIDProd(AProd, id);
                if(local!=-1){
                    setbuf(stdin,NULL);
                    printf("\nNovo nome do produto: ");
                    fgets(alt.nome,30,stdin);
                    setbuf(stdin,NULL);
                    retiraEnter(alt.nome);
                    conversorTexto(alt.nome);
                    printf("\nNova quantidade em estoque: ");
                    scanf("%d",&alt.quantidadeEstoque);
                    printf("\nNovo valor unitário: ");
                    scanf("%f",&alt.precoUnitario);

                    fseek(AProd,local*sizeof(Produto),SEEK_SET);
                    fwrite(&alt,sizeof(Produto),1,AProd);

                }else
                    printf("\nID não encontrado");

                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nDeseja Alterar outro produto?");
                printf("\n0 - Sim ... 1 - Não\n");
                scanf("%d",&sair);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }while(sair!=1);
            break;
        //Altera apenas o valor de um ou todos os Produtos
        case 1:
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nAlteração de valores");
            printf("\n0 - Um Produto ... 1 - Todos\n");
            scanf("%d",&submenu);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            //Altera o valor de um produto
            if(submenu == 0){
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o ID do produto: ");
                scanf("%d",&idProd);
                printf("0 - Descer o Preço ... 1 - Subir o Preço\n");
                scanf("%d",&sinal);
                printf("Porcentagem: ");
                scanf("%f",&porcentagem);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

                porcentagem = porcentagem/100;

                fseek(AProd,0,SEEK_SET);
                posicao = pesquisaArqIDProd(AProd,idProd);
                fseek(AProd,posicao*sizeof(Produto),SEEK_SET);
                if(sinal == 0){
                    fread(&alt,sizeof(Produto),1,AProd);
                    alt.precoUnitario -=  alt.precoUnitario * porcentagem;
                }else{
                    fread(&alt,sizeof(Produto),1,AProd);
                    alt.precoUnitario += alt.precoUnitario * porcentagem;
                }
                fseek(AProd,posicao*sizeof(Produto),SEEK_SET);
                fwrite(&alt,sizeof(Produto),1,AProd);

                hp.idProduto = idProd;
                time(&rawtime);
                info = localtime(&rawtime);
                strftime(hp.dataAlteracao,11,"%d/%m/%Y", info);
                hp.Valor = alt.precoUnitario * porcentagem;

                fseek(AHistPre,0,SEEK_CUR);
                fwrite(&hp,sizeof(HistoricoPreco),1,AHistPre);
            //Altera o valor de todos os produtos
            }else{
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("0 - Descer o Preço ... 1 - Subir o Preço\n");
                scanf("%d",&sinal);
                printf("Porcentagem: ");
                scanf("%f",&porcentagem);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

                fseek(AProd,0,SEEK_SET);
                if(sinal == 0){
                    n = 1;
                    while(fread(&alt,n*sizeof(Produto),1,AProd)){
                        alt.precoUnitario -=  alt.precoUnitario * porcentagem;

                        //Salvando a alteração do produto
                        fseek(AProd,sizeof(Produto),SEEK_CUR);
                        fwrite(&alt,sizeof(Produto),1,AProd);

                        //Salvando a alteração no arquivo HistoricoPreco
                        fseek(AHistPre,0,SEEK_CUR);
                        fwrite(&hp,sizeof(HistoricoPreco),1,AHistPre);
                        n++;
                    }
                }else{
                    n = 1;
                    while(fread(&alt,n*sizeof(Produto),1,AProd)){
                        alt.precoUnitario +=  alt.precoUnitario * porcentagem;

                        //Salvando as alterações do produto
                        fseek(AProd,sizeof(Produto),SEEK_CUR);
                        fwrite(&alt,sizeof(Produto),1,AProd);

                        //Savando as alterações no arquivo
                        fseek(AHistPre,0,SEEK_CUR);
                        fwrite(&hp,sizeof(HistoricoPreco),1,AHistPre);
                        n++;
                    }
                }
            }
            break;
        }
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Alterar outro produto?");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair!=1);
}
//Consulta feita por ID, e Prefixo do nome
void consultaProduto(FILE *AProd){

    int id,sair,local,menu;
    char pref[3];
    fseek(AProd,0,SEEK_END);

    if(ftell(AProd)>0){
        system("clear");
        do{
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nConsulta por:");
            printf("\n1-ID ... 2-Prefixo: ");
            scanf("%d",&menu);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            switch (menu){

            //Consulta por ID
            case 1:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o ID do Produto: ");
                scanf("%d",&id);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

                local = pesquisaArqIDProd(AProd, id);
                if(local!=-1)
                    printarConsultaProd(AProd,local);
                else
                    printf("\nID não Cadastrado");
                break;

            //Consulta por Prefixo
            case 2:
                setbuf(stdin,NULL);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça as 3 primeiras letras do Produto: ");
                fgets(pref,3,stdin);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                retiraEnter(pref);
                conversorTexto(pref);
                //Pesquisa no arquivo se existe o ID fornecido
                local = pesquisaArqPrefProd(AProd, pref);
                if(local!=-1)
                    printarConsultaProd(AProd,local);
                else
                    printf("Prefixo não encontrado");
                break;
            }

            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nDeseja fazer outra consulta?");
            printf("\n0 - Sim ... 1 - Não\n");
            scanf("%d",&sair);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        }while(sair!=1);
    }
}
//Lista todos os Produtos cadastrados
void listagemProduto(FILE *AProd){
    Produto list;

    fseek(AProd,0,SEEK_SET);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nListagem de Produtos Cadastrados");
    printf("\nID\tNome\tQtde\tPreço Unitário");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    while(fread(&list,sizeof(Produto),1,AProd))
        printf("\n%lu\t%s\t\t%d\tR$%.2f",list.id,list.nome,list.quantidadeEstoque,list.precoUnitario);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//Atualiza a quantidade do produto no estoques
int atualizaEstqProd(FILE *AProd, int idProd, int qtde, int sinal){

    int posicao;
    Produto prod;
    fseek(AProd,0,SEEK_SET);
    posicao = pesquisaArqIDProd(AProd,idProd);
    fseek(AProd,posicao*sizeof(Produto),SEEK_SET);
    if(sinal == 0){
        fread(&prod,sizeof(Produto),1,AProd);
        prod.quantidadeEstoque = prod.quantidadeEstoque - qtde;
    }else{
        fread(&prod,sizeof(Produto),1,AProd);
        prod.quantidadeEstoque = prod.quantidadeEstoque + qtde;
    }

    fseek(AProd,posicao*sizeof(Produto),SEEK_SET);
    fwrite(&prod,sizeof(Produto),1,AProd);

}
//Pesquisa por ID o produto no arquivo
int pesquisaArqIDProd(FILE *AProd, int id){

    int posicao = 0;
    Produto consulta;
    fseek(AProd,0,SEEK_SET);
        while(fread(&consulta,sizeof(Produto),1,AProd)){
            if(consulta.id == id)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Pesquisa por Prefixo o produto no arquivo
int pesquisaArqPrefProd(FILE *Aprod, char pref[3]){

    int posicao = 0;
    Produto consulta;
    fseek(Aprod,0,SEEK_SET);
        while(fread(&consulta,sizeof(Produto),1,Aprod) == 1){
            if(strncmp(consulta.nome,pref,2) == 0)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Printa a consulta
void printarConsultaProd(FILE *AProd, int local){
    Produto consulta;
    fseek(AProd,local*sizeof(Produto),SEEK_SET);
    fread(&consulta,sizeof(Produto),1,AProd);
    printf("\n~~~~~~~~~~~ Produto ~~~~~~~~~~~");
    printf("\nID: %lu",consulta.id);
    printf("\nNome: %s",consulta.nome);
    printf("\nQuantidade: %u",consulta.quantidadeEstoque);
    printf("\nPreço Unitário: %.2f",consulta.precoUnitario);
}
//Localiza o ultimo ID cadastrado dos Produtos e coloca como + 1 para o proximo
int gerarIDProd(FILE *AProd){
    long pegarID = 0;
    Produto produto;
    fseek(AProd,0,SEEK_END);
    pegarID = ftell(AProd);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(AProd,pegarID-sizeof(Produto),SEEK_SET);
        fread(&produto,sizeof(Produto),1,AProd);
        pegarID = produto.id + 1;
        return pegarID;
    }
}
