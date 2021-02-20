#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "utilitarios.h"

//Cadastra novos Clientes
void cadastroCliente(FILE *ACli){

    int CPFValido = 1, CPFExistente = -1, sair = 0;
    Cliente novo;

    do{
        system("clear");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        novo.id = gerarIDCli(ACli);
        setbuf(stdin,NULL);
        printf("\nNome do Cliente: ");
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
            CPFExistente = pesquisaArqCPFCli(ACli,novo.cpf);
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

        fseek(ACli,0,SEEK_END);
        fwrite(&novo,sizeof(Cliente),1,ACli);

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Cadastrar outro cliente?");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair != 1);

}
//Faz alteração de Cliente
void alteracaoCliente(FILE *ACli){

    int id,sair,local, CPFValido = 1;
    Cliente alt;

    do{
        system("clear");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nForneça o ID do Cliente: ");
        scanf("%d",&id);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        fseek(ACli,0,SEEK_SET);
        local = pesquisaArqIDCli(ACli, id);
        if(local!=-1){
            setbuf(stdin,NULL);
            printf("\nNovo nome do cliente: ");
            fgets(alt.nome,100,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.nome);
            conversorTexto(alt.nome);
            printf("\nNovo CPF do cliente: ");
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
            retiraEnter(alt.email);
            printf("\nNovo Telefone: ");
            fgets(alt.telefone,15,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.telefone);

            fseek(ACli,local*sizeof(Cliente),SEEK_SET);
            fwrite(&alt,sizeof(Cliente),1,ACli);
        }else
            printf("\nID não encontrado");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Alterar outro cliente?");
        printf("\n 0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair!=1);
}
//Consulta feita por id, cpf e/ou prefixo do nome, chama a função de pesquisa necessária
void consultaCliente(FILE *ACli){

    int id,sair,local,menu;
    char cpf[12],pref[3];
    fseek(ACli,0,SEEK_END);

    if(ftell(ACli)>0){
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
                printf("\nForneça o ID do Cliente: ");
                scanf("%d",&id);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                //Pesquisa no arquivo se existe o ID fornecido
                local = pesquisaArqIDCli(ACli, id);
                if(local!=-1)
                    printarConsultaCli(ACli,local);
                else
                    printf("ID não Cadastrado");
                break;

            //Consulta por CPF
            case 2:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o CPF do Cliente: ");
                setbuf(stdin,NULL);
                fgets(cpf,12,stdin);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                //Pesquisa no arquivo se existe o CPF fornecido
                local = pesquisaArqCPFCli(ACli,cpf);
                if(local!=-1)
                    printarConsultaCli(ACli,local);
                else
                    printf("CPF não Cadastrado");
                break;

            //Consulta por Prefixo
            case 3:
                setbuf(stdin,NULL);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça as 3 primeiras letras do Cliente: ");
                fgets(pref,3,stdin);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                retiraEnter(pref);
                conversorTexto(pref);
                //Pesquisa no arquivo se existe o ID fornecido
                local = pesquisaArqPrefCli(ACli, pref);
                if(local!=-1)
                    printarConsultaCli(ACli,local);
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
    else
        printf("\nNenhum Cliente cadastrado");
}
//Lista todos os Clientes cadastrados
void listagemCliente(FILE *ACli){

    Cliente list;
    system("clear");
    fseek(ACli,0,SEEK_SET);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nListagem de Clientes Cadastrados");
    printf("\nID\tNome");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    while(fread(&list,sizeof(Cliente),1,ACli))
        printf("\n%lu\t%s",list.id,list.nome);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//Pesquisando existencia do ID fornecido no arquivo Cliente e retorna sua posição
int pesquisaArqIDCli(FILE *ACli, int id){
    int posicao = 0;
    Cliente consulta;
    fseek(ACli,0,SEEK_SET);
        while(fread(&consulta,sizeof(Cliente),1,ACli) == 1){
            if(consulta.id == id)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Pesquisando existencia do CPF fornecido no arquivo Cliente
int pesquisaArqCPFCli(FILE *ACli, char cpf[12]){
    int posicao = 0;
    Cliente consulta;
    fseek(ACli,0,SEEK_SET);
        while(fread(&consulta,sizeof(Cliente),1,ACli) == 1){
            if(strcmp(consulta.cpf,cpf) == 0)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Pesquisando existencia do Prefixo fornecido no arquivo Cliente
int pesquisaArqPrefCli(FILE *ACli, char pref[3]){

    int posicao = 0;
    Cliente consulta;
    fseek(ACli,0,SEEK_SET);
        while(fread(&consulta,sizeof(Cliente),1,ACli) == 1){
            if(strncmp(consulta.nome,pref,2) == 0)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Printa a Consulta
void printarConsultaCli(FILE *ACli, int local){
    Cliente consulta;
    fseek(ACli,local*sizeof(Cliente),SEEK_SET);
    fread(&consulta,sizeof(Cliente),1,ACli);
    printf("\n~~~~~~~ Perfil do Cliente ~~~~~~~");
    printf("\nID: %lu",consulta.id);
    printf("\nNome: %s",consulta.nome);
    printf("\nCPF: %s", consulta.cpf);
    printf("\nE-mail: %s",consulta.email);
    printf("\nTelefone: %s",consulta.telefone);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//Localiza o ultimo ID cadastrado dos Clientes e coloca como + 1 para o proximo
int gerarIDCli(FILE *ACli){
    long pegarID = 0;
    Cliente cliente;
    fseek(ACli,0,SEEK_END);
    pegarID = ftell(ACli);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(ACli,pegarID-sizeof(Cliente),SEEK_SET);
        fread(&cliente,sizeof(Cliente),1,ACli);
        pegarID = cliente.id + 1;
        return pegarID;
    }
}
