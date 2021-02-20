#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "venda.h"
#include "cliente.h"
#include "vendedor.h"
#include "produto.h"
#include "utilitarios.h"


//Venda de produtos para Clientes
void venda(FILE *AVend, FILE *ACli, FILE *AProd, FILE *ANota, FILE *AINota){

    int valVend = 0,valCli = 0,idCli, valData = 1;  //Validação Vendedor, Cliente e Data
    char cpf[12], password[20],localVend;           //Validação login Vendedor
    int sairVenda,sair,sairCarrinho;                //Menu
    int idProd,n,local,qtde;                        //Venda
    int i = 0, j = 0;                               //Contadores
    struct tm *info;                                //Data
    time_t rawtime;                                 //Data

    Carrinho *car;
    Produto prod;
    NotaFiscal nf;
    ItemNotaFiscal infiscal;
    Vendedor consulta;

    system("clear");
    setbuf(stdin,NULL);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nForneça o CPF do Vendedor: ");
    fgets(cpf,12,stdin);
    setbuf(stdin,NULL);
    retiraEnter(cpf);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nForneça a senha: ");
    fgets(password,20,stdin);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    setbuf(stdin,NULL);
    retiraEnter(password);

    //Validando o Vendedor
    do{
        valVend = verificaVendedor(AVend,cpf,password);
        if(valVend == 0){
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nCPF ou senha Inválida");
            printf("\nForneça o CPF do Vendedor: ");
            fgets(cpf,12,stdin);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            setbuf(stdin,NULL);
            retiraEnter(cpf);
            printf("\nForneça a senha: ");
            fgets(password,20,stdin);
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            setbuf(stdin,NULL);
            retiraEnter(password);
        }
    }while(valVend == 0);

    do{
        //Validando o Cliente utiliando a função "pesquisaArqIDCli()"
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nForneça o ID do Cliente: ");
        scanf("%d",&idCli);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        do{
            if(valCli == -1){
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nID do Cliente inválido");
                printf("\nForneça o ID do Cliente");
                scanf("%d",&idCli);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }
            valCli = pesquisaArqIDCli(ACli, idCli);
        }while(valCli == -1);

        //Inicia o carrinho, vetor dinamico iniciando com 1, a cada produto que o cliente
        //for adicionar ao carrinho, o programa realoca o vetor acrescentando mais um epaço
        n = 1;
        car = (Carrinho*)malloc(n*sizeof(Carrinho)); //alocação de 1 espaço no valor de n
        do{
            system("clear");

            //Lista os produtos em estoque
            listagemProduto(AProd);

            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nForneça um id do Produto: ");
            scanf("%d",&idProd);
            local = pesquisaArqIDProd(AProd,idProd); //Pesqisa se existe ou n o produto, e retorna sua posição


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
                    printf("Quantidade: ");
                    scanf("%d",&qtde);

                    //Verifica se a quantidade requerida está disponível no estoque

                    fseek(AProd,local*sizeof(Produto),SEEK_SET);
                    fread(&prod,sizeof(Produto),1,AProd);
                        if(prod.quantidadeEstoque >= qtde){
                            car[n-1].quantidadeVendida = qtde;
                            car[n-1].valorVenda = prod.precoUnitario;
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
                car = realloc(car,n);  //realoca acrescentando +1 espaço, n++ ao aceitar +1 produto
            }
        }while(sairCarrinho != 1);

        nf.valorTotal = 0;
        nf.id = gerarIDNota(ANota);
        nf.idCliente = idCli;
        localVend = pesquisaArqCPFVend(AVend, cpf);
        fseek(AVend,localVend*sizeof(Vendedor),SEEK_SET);
        fread(&consulta,sizeof(Vendedor),1,AVend);
        nf.idVendedor = consulta.id;
        for(i=0;i<=n;i++){
            nf.valorTotal += car[i].valorVenda * car[i].quantidadeVendida;
        }

        //Printando o Carrinho
        system("clear");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nCarrinho");
        printf("\nID\t\tQuantidade");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for(i=0;i<n;i++)
            printf("\n%lu\t\t%d",car[i].idProduto,car[i].quantidadeVendida);

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja alterar algum produto");
        printf("\n0-Sim ... 1-Não\n");
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
                        car[i].quantidadeVendida = qtde;
                        car[i].valorVenda = prod.precoUnitario;
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

        //Atualizar o estoque da farmacia
        for(i=0;i<n;i++)
            atualizaEstqProd(AProd, car[i].idProduto, car[i].quantidadeVendida,0);


        //Datando a Nota Fiscal
        system("clear");
        printf("\nAplicar a Data da Nota Fiscal");
        printf("\n0-Manual ... 1-Automático\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        if(sair == 1){
            time(&rawtime);
            info = localtime(&rawtime);
            strftime(nf.dataCompra,11,"%d/%m/%Y", info);
        }else{
            setbuf(stdin,NULL);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nForneça a Data: dd/mm/aaaa");
            fgets(nf.dataCompra,11,stdin);
            retiraEnter(nf.dataCompra);
            do{
                if(valData == 0){
                    setbuf(stdin,NULL);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                    printf("\nData Inválida");
                    printf("\nForneça uma data Válida: dd/mm/aaaa");
                    fgets(nf.dataCompra,11,stdin);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                    retiraEnter(nf.dataCompra);
                }
                valData = verificaData(nf.dataCompra);
            }while(valData != 1);
        }


        //Printar a nota Fiscal
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~~~~~ Nota Fiscal ~~~~~~~~~");
        printf("\nID: %lu",nf.id);
        printf("\nID Cliente: %lu",nf.idCliente);
        printf("\nID Vendedor: %lu",nf.idVendedor);
        printf("\nValor Total: %.2f",nf.valorTotal);
        printf("\nData: %s",nf.dataCompra);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");



        //Registro de Item Nota Fiscal para cada produto vendido
        for(i=0;i<n;i++){
            infiscal.id = gerarIDItemNotaFiscal(AINota);
            infiscal.idProduto = car[i].idProduto;
            infiscal.idNotaFiscal = nf.id;
            infiscal.quantidade = car[i].quantidadeVendida;
            infiscal.valorVenda = car[i].valorVenda;
            fseek(AINota,0,SEEK_END);
            fwrite(&infiscal,sizeof(ItemNotaFiscal),1,AINota);
        }

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nCompra efetuada com sucesso");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        fseek(ANota,0,SEEK_END);
        fwrite(&nf,sizeof(NotaFiscal),1,ANota);

        printf("\nDeseja efetuar outra venda?");
        printf("\n0-Sim ... 1-Não: ");
        scanf("%d",&sairVenda);
    }while(sairVenda != 1);
}
//Loga o vendedor com o login e senha fornecido
int verificaVendedor(FILE *AVend, char cpf[12], char password[20]){

    Vendedor consulta;
    fseek(AVend,0,SEEK_SET);
        while(fread(&consulta,sizeof(Vendedor),1,AVend) == 1){
            if(strcmp(consulta.cpf,cpf) == 0){
                if(strcmp(consulta.password,password) == 0)
                    return consulta.id; //Valido
                else{
                    printf("\nSenha inválida");
                    return 0; //Password inválido
                }
            }else{
                printf("\nCPF inválido");
                return 0;  //CPF Inválido
            }
        }
        return 0;
}
//Gerar ID para Nota Fiscal
int gerarIDNota(FILE *ANota){
    long pegarID = 0;
    NotaFiscal nota;
    fseek(ANota,0,SEEK_END);
    pegarID = ftell(ANota);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(ANota,pegarID-sizeof(NotaFiscal),SEEK_SET);
        fread(&nota,sizeof(NotaFiscal),1,ANota);
        pegarID = nota.id + 1;
        return pegarID;
    }
}
//Gerar ID para nota de item
int gerarIDItemNotaFiscal(FILE *AINota){
    long pegarID = 0;
    ItemNotaFiscal itemNota;
    fseek(AINota,0,SEEK_END);
    pegarID = ftell(AINota);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(AINota,pegarID-sizeof(itemNota),SEEK_SET);
        fread(&itemNota,sizeof(ItemNotaFiscal),1,AINota);
        pegarID = itemNota.id + 1;
        return pegarID;
    }
}
