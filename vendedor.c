#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendedor.h"
#include "utilitarios.h"

//Cadastra novos Vendedores
void cadastroVendedor(FILE *AVend){

    int CPFValido = 1, CPFExistente = -1, sair = 0;
    Vendedor novo;

    do{
        system("clear");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        novo.id = gerarIDVend(AVend);
        setbuf(stdin,NULL);
        printf("\nNome do Vendedor: ");
        fgets(novo.nome,100,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.nome);
        conversorTexto(novo.nome);
        printf("\nCPF: ");
        fgets(novo.cpf,12,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.cpf);
        do{
            if(CPFValido == 0 || CPFExistente != -1){
                printf("\nForneça um CPF Válido: ");
                fgets(novo.cpf,12,stdin);
                setbuf(stdin,NULL);
                retiraEnter(novo.cpf);
            }
            CPFValido = verificaCPF(novo.cpf);
            CPFExistente = pesquisaArqCPFVend(AVend,novo.cpf);
            if(CPFExistente != -1)
                printf("\nCPF já cadastrado: ");
        }while(CPFValido == 0 || CPFExistente != -1);
        setbuf(stdin,NULL);
        printf("\nE-mail: ");
        fgets(novo.email,50,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.email);
        printf("\nTelefone: ");
        fgets(novo.telefone,15,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.telefone);
        printf("\nForneça uma senha para utilização: ");
        fgets(novo.password,20,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.password);

        fseek(AVend,0,SEEK_END);
        fwrite(&novo,sizeof(Vendedor),1,AVend);

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Cadastrar outro vendedor?");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair != 1);
}
//Altera Vendedor
void alteracaoVendedor(FILE *AVend){

    int id,sair,local, CPFValido = 1;
    Vendedor alt;

    do{
        system("clear");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nForneça o ID do Vendedor: ");
        scanf("%d",&id);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        fseek(AVend,0,SEEK_SET);
        local = pesquisaArqIDVend(AVend, id);
        if(local!=-1){
            setbuf(stdin,NULL);
            printf("\nNovo nome do vendedor: ");
            fgets(alt.nome,100,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.nome);
            conversorTexto(alt.nome);
            printf("\nNovo CPF: ");
            fgets(alt.cpf,12,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.cpf);
            do{
                if(CPFValido == 0){
                    printf("\nForneça um CPF Válido: ");
                    fgets(alt.cpf,12,stdin);
                    setbuf(stdin,NULL);
                    retiraEnter(alt.cpf);
                }
                CPFValido = verificaCPF(alt.cpf);
            }while(CPFValido == 0);
            setbuf(stdin,NULL);
            printf("\nNovo e-mail: ");
            fgets(alt.email,50,stdin);
            setbuf(stdin,NULL);
            printf("\nNovo Telefone: ");
            fgets(alt.telefone,15,stdin);
            setbuf(stdin,NULL);
            printf("\nForneça a nova senha: ");
            fgets(alt.password,20,stdin);
            setbuf(stdin,NULL);

            fseek(AVend,local*sizeof(Vendedor),SEEK_SET);
            fwrite(&alt,sizeof(Vendedor),1,AVend);
        }else
            printf("\nID não encontrado");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Alterar outro Vendedor?");
        printf("\n0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair!=1);
}
//Consulta por ID, CPF ou Prefixo
void consultaVendedor(FILE *AVend){

    int id,sair,local,menu;
    char cpf[12], pref[3];
    fseek(AVend,0,SEEK_END);

    if(ftell(AVend)>0){
        system("clear");
        do{
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nConsulta por:");
            printf("\n1-ID ... 2-CPF ... 3-Prefixo\n");
            scanf("%d",&menu);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            switch (menu){

            //Consulta por ID
            case 1:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o ID do Vendedor: ");
                scanf("%d",&id);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                //Pesquisa np arquivo se existe o id fornecido
                local = pesquisaArqIDVend(AVend, id);
                if(local!=-1)
                    printarConsultaVend(AVend,local);
                else
                    printf("ID não Cadastrado");
                break;

            //Consulta por CPF
            case 2:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o CPF do Vendedor: ");
                setbuf(stdin,NULL);
                fgets(cpf,12,stdin);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                //Pesquisa no arquivo se existe o CPF fornecido
                local = pesquisaArqCPFVend(AVend,cpf);
                if(local!=-1)
                    printarConsultaVend(AVend,local);
                else
                    printf("CPF não Cadastrado");
                break;

            //Consulta por Prefixo
            case 3:
                setbuf(stdin,NULL);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça as 3 primeiras letras do Vendedor: ");
                fgets(pref,3,stdin);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                retiraEnter(pref);
                conversorTexto(pref);
                //Pesquisa no se existe um vendendor com o Prefixo fornecido
                local = pesquisaArqPrefVend(AVend, pref);
                if(local!=-1)
                    printarConsultaVend(AVend,local);
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
    }else
        printf("\nNenhum Vendedor cadastrado");
}
//Lista todos os Vendedores cadastrados
void listagemVendedor(FILE *AVend){

    Vendedor list;
    system("clear");
    fseek(AVend,0,SEEK_SET);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nListagem de Vendedores Cadastrados");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nID\t\t Nome");

    while(fread(&list,sizeof(Vendedor),1,AVend))
        printf("\n%lu\t\t%s",list.id,list.nome);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//Pesquisando existencia do ID fornecido no arquivo Vendedor e retorna sua posição
int pesquisaArqIDVend(FILE *AVend, int id){
    int posicao = 0;
    Vendedor consulta;
    fseek(AVend,0,SEEK_SET);
        while(fread(&consulta,sizeof(Vendedor),1,AVend) == 1){
            if(consulta.id == id)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Pesquisando existencia do CPF fornecido no arquivo Vendedor
int pesquisaArqCPFVend(FILE *AVend, char cpf[12]){
    int posicao = 0;
    Vendedor consulta;
    fseek(AVend,0,SEEK_SET);
        while(fread(&consulta,sizeof(Vendedor),1,AVend) == 1){
            if(strcmp(consulta.cpf,cpf) == 0)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Pesquisando existencia do Prefixo fornecido no arquivo Vendedor
int pesquisaArqPrefVend(FILE *AVend, char pref[2]){

    int posicao = 0;
    Vendedor consulta;
    fseek(AVend,0,SEEK_SET);
        while(fread(&consulta,sizeof(Vendedor),1,AVend) == 1){
            if(strncmp(consulta.nome,pref,2) == 0)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Printa a Consulta
void printarConsultaVend(FILE *AVend, int local){
    Vendedor consulta;
    fseek(AVend,local*sizeof(Vendedor),SEEK_SET);
    fread(&consulta,sizeof(Vendedor),1,AVend);
    printf("\n~~~~~~ Perfil do Vendedor ~~~~~~");
    printf("\nID: %lu",consulta.id);
    printf("\nNome: %s",consulta.nome);
    printf("\nCPF: %s", consulta.cpf);
    printf("\nE-mail: %s",consulta.email);
    printf("\nTelefone: %s",consulta.telefone);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//Localiza o ultimo ID cadastrado dos Vendedores e coloca como + 1 para o proximo
int gerarIDVend(FILE *AVend){
    long pegarID = 0;
    Vendedor vendedor;
    fseek(AVend,0,SEEK_END);
    pegarID = ftell(AVend);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(AVend,pegarID-sizeof(Vendedor),SEEK_SET);
        fread(&vendedor,sizeof(Vendedor),1,AVend);
        pegarID = vendedor.id + 1;
        return pegarID;
    }
}
