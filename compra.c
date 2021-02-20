#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "compra.h"
#include "produto.h"
#include "fornecedor.h"
#include "utilitarios.h"


//Compra de produtos para a farmacia
int compra(FILE *AProd, FILE *AForn, FILE *ANotaComp, FILE *AINotaComp){

    int sair = 0,sairCompra = 0,sairCarrinho = 0;       //Menu
    int idForn, valForn = 1, local, valData = 1;        //Validador
    int idProd, qtde;                                   //Compra
    int i = 0, n = 0, j = 0;                            //Contador
    struct tm *info;                                    //Data
    time_t rawtime;                                     //Data

    CarrinhoCompra *car;
    NotaCompra nfc;
    Produto prod;
    ItemNotaCompra incomp;

    do{
        system("clear");
        printf("\nForneça o id do Fornecedor: ");
        scanf("%d",&idForn);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        do{
            if(valForn < 0){
                printf("\nID Inválido");
                printf("\nForneça um id Válido: ");
                scanf("%d",&idForn);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            }

            valForn = pesquisaArqIDForn(AForn,idForn);
        }while(valForn < 0);


        n = 1;
        car = (CarrinhoCompra*)malloc(n*sizeof(car)); //alocação de 1 espaço no valor de n

        do{
            system("clear");

            listagemProduto(AProd);

            printf("\nForneça o id do produto: ");
            scanf("%d",&idProd);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            local = pesquisaArqIDProd(AProd, idProd);

            do{
                if(local >= 0){
                    //Verifica se no carrinho ja existe um produto com o ID fornecido
                    do{
                        if(car[i].idProduto == idProd){
                            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                            printf("\nProduto ja cadastrado no carrinho");
                            printf("\nForneça o id do Produto");
                            scanf("%d",&idProd);
                            local = pesquisaArqIDProd(AProd,idProd);
                            break;
                        }else
                            i++;
                    }while(i<=n);
                    car[n-1].idProduto = idProd;
                    printf("\nQuantidade: ");
                    scanf("%d",&qtde);

                    //Verifica se a quantidade requerida está disponível no estoque
                    fread(&prod, sizeof(Produto),local,AProd); 
                    if(prod.quantidadeEstoque >= qtde){        
                        car[n-1].quantidade = qtde;         
                        car[n-1].valorUnitario = prod.precoUnitario;
                    }
                    sair = 1;
                }else{
                    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                    printf("\nForneça um id válido: ");
                    scanf("%d",&idProd);
                    local = pesquisaArqIDProd(AProd,idProd);
                    sair = 0;
                }
            }while(sair!=1);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nDeseja acrescentar mais Produtos ao carrinho?");
                printf("\n0-Sim ... 1-Não\n");
                scanf("%d",&sairCarrinho);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                if(sairCarrinho == 0){
                    n++;
                    car = realloc(car,n);   //realoca acrescentando +1 espaço, n++ ao aceitar +1 produto
                }
        }while(sairCarrinho != 1);


        //Printando o Carrinho
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nCarrinho");
        printf("\nID\t\tQuantidade");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for(i=0;i<n;i++)
            printf("\n%lu\t\t%d",car[i].idProduto,car[i].quantidade);

        printf("\nDeseja alterar algum produto");
        printf("\n0-Sim ... 1-Não");
        scanf("%d",&sair);

        //Excluir e/ou alterar os produtos do carrinho
        while(sair != 1){
            printf("\nID do produto para alterar: ");
            scanf("%d",&idProd);
            for(i=0;i<n;i++){
                if(idProd == car[i].idProduto){
                    j=1;
                    break; 
                }
            }
            if(j=1){
                printf("\nForneça a nova quantidade: ");
                scanf("%d",&qtde);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

                fread(&prod, sizeof(Produto),local,AProd); 
                    if(prod.quantidadeEstoque >= qtde){        
                        car[i].quantidade = qtde;         
                        car[i].valorUnitario = prod.precoUnitario;
                    }
                    sair = 1;
            }else
                printf("\nID não encontrado");
            
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("Deseja alterar outro produto?");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("0-Sim ... 1-Não ");
            scanf("%d",&sair);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        }

        //Salvando na nota fiscal
        nfc.id = gerarIDNotaCompra(ANotaComp);
        nfc.idFornecedor = idForn;
        for(i=0;i<=n;i++){
            nfc.valorTotal += car[i].valorUnitario * car[i].quantidade;
        }

        //Atualizar o estoque da farmacia
        for(i=0;i<n;i++)
            atualizaEstqProd(AProd, car[i].idProduto, car[i].quantidade,1);


        //Datando a Nota Fiscal
        printf("\nAplicar a Data da Nota Fiscal");
        printf("\n0-Manual ... 1-Automático");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        if(sair == 1){
            time(&rawtime);
            info = localtime(&rawtime);
            strftime(nfc.dataCompra,11,"%d/%m/%Y", info);
        }else{
            setbuf(stdin,NULL);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nForneça a Data: dd/mm/aaaa");
            fgets(nfc.dataCompra,11,stdin);
            retiraEnter(nfc.dataCompra);    
            do{
                if(valData == 0){
                    setbuf(stdin,NULL);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                    printf("\nData Inválida");
                    printf("\nForneça uma data Válida: dd/mm/aaaa");
                    fgets(nfc.dataCompra,11,stdin);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                    retiraEnter(nfc.dataCompra);
                }
                valData = verificaData(nfc.dataCompra);
            }while(valData != 1);
        }

        //Printar a nota Fiscal
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~~~~~ Nota Fiscal ~~~~~~~~~");
        printf("\nID: %lu",nfc.id);
        printf("\nID Fornecedor: %lu",nfc.idFornecedor);
        printf("\nValor Total: %f",nfc.valorTotal);
        printf("\nData: %s",nfc.dataCompra);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");


        //Registro de Item Nota Fiscal para cada produto vendido
        for(i=0;i<n;i++){
            incomp.id = gerarIDItemNotaCompra(AINotaComp);
            incomp.idProduto = car[i].idProduto;
            incomp.idNotaCompra = nfc.id;
            incomp.quantidade = car[i].quantidade;
            incomp.ValorUnitario = car[i].valorUnitario;
            fseek(AINotaComp,0,SEEK_END);
            fwrite(&incomp,sizeof(ItemNotaCompra),1,AINotaComp);
        }


        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nCompra efetuada com sucesso");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        fseek(ANotaComp,0,SEEK_END);
        fwrite(&nfc,sizeof(NotaCompra),1,ANotaComp);


        printf("\nDeseja continuar comprando");
        printf("\n0-Sim ... 1-Não");
        scanf("%d",&sairCompra);
    }while(sairCompra != 1);
    return 0;
}
//Gerar ID da nota fiscal
int gerarIDNotaCompra(FILE *ANotaComp){
    long pegarID = 0;
    NotaCompra nota;
    fseek(ANotaComp,0,SEEK_END);
    pegarID = ftell(ANotaComp);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(ANotaComp,pegarID-sizeof(NotaCompra),SEEK_SET);
        fread(&nota,sizeof(NotaCompra),1,ANotaComp);
        pegarID = nota.id + 1;
        return pegarID;
    }
}
//Gerar ID de item da nota Compra
int gerarIDItemNotaCompra(FILE *AINotaComp){
    long pegarID = 0;
    ItemNotaCompra itemNota;
    fseek(AINotaComp,0,SEEK_END);
    pegarID = ftell(AINotaComp);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(AINotaComp,pegarID-sizeof(ItemNotaCompra),SEEK_SET);
        fread(&itemNota,sizeof(ItemNotaCompra),1,AINotaComp);
        pegarID = itemNota.id + 1;
        return pegarID;
    }
}