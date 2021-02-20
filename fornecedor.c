#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornecedor.h"
#include "utilitarios.h"

//Cadastra novos Fornecedores
void cadastroFornecedor(FILE *AForn){

    int CNPJValido = 1, CNPJExistente = -1, sair = 0;
    Fornecedor novo;

    do{
        system("clear");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        novo.id = gerarIDForn(AForn);
        setbuf(stdin,NULL);
        printf("\nNome do Fornecedor: ");
        fgets(novo.nome,100,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.nome);
        conversorTexto(novo.nome);
        printf("\nCNPJ: ");
        fgets(novo.CNPJ,15,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.CNPJ);
        do{
            if(CNPJValido == 0 || CNPJExistente != -1){
                printf("\nForneça um CNPJ Válido: ");
                fgets(novo.CNPJ,15,stdin);
                setbuf(stdin,NULL);
                retiraEnter(novo.CNPJ);
            }
            CNPJValido = verificaCNPJ(novo.CNPJ);
            CNPJExistente = pesquisaArqCNPJForn(AForn,novo.CNPJ);
            if(CNPJExistente != -1)
                printf("\nCNPJ já cadastrado");
        }while(CNPJValido == 0 || CNPJExistente != -1);
        setbuf(stdin,NULL);
        printf("\nE-mail: ");
        fgets(novo.email,50,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.email);

        printf("\nTelefone: ");
        fgets(novo.telefone,15,stdin);
        setbuf(stdin,NULL);
        retiraEnter(novo.telefone);

        fseek(AForn,0,SEEK_END);
        fwrite(&novo,sizeof(Fornecedor),1,AForn);

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Cadastrar outro fornecedor?");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair != 1);
}
//Altera Fornecedor
void alteracaoFornecedor(FILE *AForn){

    int id,sair,local, CNPJValido = 1;
    Fornecedor alt;

    do{
        system("clear");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nForneça o ID do Fornecedor: ");
        scanf("%d",&id);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        fseek(AForn,0,SEEK_SET);
        local = pesquisaArqIDForn(AForn, id);
        if(local!=-1){

            setbuf(stdin,NULL);
            printf("\nNovo nome do fornecedor: ");
            fgets(alt.nome,100,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.nome);
            conversorTexto(alt.nome);
            printf("\nNovo CNPJ: ");
            fgets(alt.CNPJ,15,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.CNPJ);
            do{
                if(CNPJValido == 0){
                    printf("\nForneça um CNPJ Válido: ");
                    fgets(alt.CNPJ,15,stdin);
                    setbuf(stdin,NULL);
                    retiraEnter(alt.CNPJ);
                }
                CNPJValido = verificaCNPJ(alt.CNPJ);
            }while(CNPJValido == 0);
            setbuf(stdin,NULL);
            printf("\nNovo e-mail: ");
            fgets(alt.email,50,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.email);

            printf("\nNovo Telefone: ");
            fgets(alt.telefone,15,stdin);
            setbuf(stdin,NULL);
            retiraEnter(alt.telefone);

            fseek(AForn,local*sizeof(Fornecedor),SEEK_SET);
            fwrite(&alt,sizeof(Fornecedor),1,AForn);
        }else
            printf("\nID não encontrado");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nDeseja Alterar outro Fornecedor?");
        printf("\n0 - Sim ... 1 - Não\n");
        scanf("%d",&sair);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }while(sair!=1);
}
//Consulta por ID, CNPJ ou Prefixo
void consultaFornecedor(FILE *AForn){

    int id,sair,local,menu;
    char cnpj[12], pref[3];
    fseek(AForn,0,SEEK_END);

    if(ftell(AForn)>0){
        system("clear");
        do{
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("\nConsulta por:");
            printf("\n1-ID ... 2-CNPJ ... 3-Prefixo\n");
            scanf("%d",&menu);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            switch (menu){

            //Consulta por ID
            case 1:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o ID do Fornecedor: ");
                scanf("%d",&id);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                //Pesquisa np arquivo se existe o id fornecido
                local = pesquisaArqIDForn(AForn, id);
                if(local!=-1){
                    printarConsultaForn(AForn,local);
                }
                else
                    printf("\\nID não Cadastrado");
                break;
            //Consulta por CNPJ
            case 2:
                setbuf(stdin,NULL);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça o CNPJ do Fornecedor: ");
                fgets(cnpj,15,stdin);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                //Pesquisa no arquivo se existe o CNPJ fornecido
                local = pesquisaArqCNPJForn(AForn, cnpj);
                if(local!=-1)
                    printarConsultaForn(AForn,local);
                else
                    printf("CNPJ não Cadastrado");
                break;

            //Consulta por Prefixo
            case 3:
                setbuf(stdin,NULL);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça as 3 primeiras letras do Fornecedor: ");
                fgets(pref,3,stdin);
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                retiraEnter(pref);
                conversorTexto(pref);
                //Pesquisa no se existe um vendendor com o Prefixo fornecido
                local = pesquisaArqPrefForn(AForn, pref);
                if(local!=-1)
                    printarConsultaForn(AForn,local);
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
        printf("\nNenhum Fornecedor cadastrado");
}
//Lista todos os Fornecedores cadastrados
void listagemFornecedor(FILE *AForn){

    Fornecedor list;
    system("clear");
    fseek(AForn,0,SEEK_SET);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nListagem de Fornecedores Cadastrados");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nID\t\t Nome");

    while(fread(&list,sizeof(Fornecedor),1,AForn))
        printf("\n%lu\t\t%s",list.id,list.nome);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}
//Pesquisando existencia do ID fornecido no arquivo Fornecedor e retorna sua posição
int pesquisaArqIDForn(FILE *AForn, int id){
    int posicao = 0;
    Fornecedor consulta;
    fseek(AForn,0,SEEK_SET);
        while(fread(&consulta,sizeof(Fornecedor),1,AForn) == 1){
            if(consulta.id == id)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Pesquisando existencia do CNPJ fornecido no arquivo Fornecedor
int pesquisaArqCNPJForn(FILE *AForn, char cnpj[15]){
    int posicao = 0;
    Fornecedor consulta;
    fseek(AForn,0,SEEK_SET);
        while(fread(&consulta,sizeof(Fornecedor),1,AForn) == 1){
            if(strcmp(consulta.CNPJ,cnpj) == 0)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Pesquisando existencia do Prefixo fornecido no arquivo Fornecedor
int pesquisaArqPrefForn(FILE *AForn, char pref[3]){

    int posicao = 0;
    Fornecedor consulta;
    fseek(AForn,0,SEEK_SET);
        while(fread(&consulta,sizeof(Fornecedor),1,AForn) == 1){
            if(strncmp(consulta.nome,pref,2) == 0)
                return posicao;
            else
                posicao++;
        }
        return -1;
}
//Printa a Consulta
void printarConsultaForn(FILE *AForn, int local){
    Fornecedor consulta;
    fseek(AForn,local*sizeof(Fornecedor),SEEK_SET);
    fread(&consulta,sizeof(Fornecedor),1,AForn);
    printf("\n~~~~~ Perfil do Fornecedor ~~~~~~");
    printf("\nID: %lu",consulta.id);
    printf("\nNome: %s",consulta.nome);
    printf("\nCPF: %s", consulta.CNPJ);
    printf("\nE-mail: %s",consulta.email);
    printf("\nTelefone: %s",consulta.telefone);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//Localiza o ultimo ID cadastrado dos Fornecedores e coloca como + 1 para o proximo
int gerarIDForn(FILE *AForn){
    long pegarID = 0;
    Fornecedor fornecedor;
    fseek(AForn,0,SEEK_END);
    pegarID = ftell(AForn);
    if(pegarID == 0){        //Se o ftell retornar 0, considera como primeiro cliente cadastrado, ID = 1;
        pegarID = 1;
        return pegarID;
    }else{              //Ftell retornando tamanho do arquivo e assim salvando o ultimo id + 1 para novo.
        fseek(AForn,pegarID-sizeof(Fornecedor),SEEK_SET);
        fread(&fornecedor,sizeof(Fornecedor),1,AForn);
        pegarID = fornecedor.id + 1;
        return pegarID;
    }
}
