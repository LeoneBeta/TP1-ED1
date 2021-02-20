#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utilitarios.h"

//Tenta abrir todos os arquivos com aw+, caso não exista os arquivos, cria novos com wb+
void abrirArquivos(FILE **ACli, FILE **AVend, FILE **AForn, FILE **ANota, FILE **AINota, FILE **AProd,
                   FILE **ANotaComp, FILE **AINotaComp, FILE **AHistPre){

    *ACli = fopen("Clientes.dat","rb+");
    *AVend = fopen("Vendedor.dat","rb+");
    *AForn = fopen("Fornecedor.dat","rb+");
    *ANota = fopen("NotaFiscal.dat","rb+");
    *AINota = fopen("ItemNotaFiscal.dat","rb+");
    *AProd = fopen("Produto.dat","rb+");
    *ANotaComp = fopen("NotaCompra.dat","rb+");
    *AINotaComp = fopen("ItemNotaCompra.dat","rb+");
    *AHistPre = fopen("HistoricoPreco.dat","rb+");

    if(*ACli == NULL)
        *ACli = fopen("Clientes.dat","wb+");
    if(*AVend == NULL)
        *AVend = fopen("Vendedor.dat","wb+");
    if(*AForn == NULL)
        *AForn = fopen("Fornecedor.dat","wb+");
    if(*ANota == NULL)
        *ANota = fopen("NotaFiscal.dat","wb+");
    if(*AINota == NULL)
        *AINota = fopen("ItemNotaFiscal.dat","wb+");
    if(*AProd == NULL)
        *AProd = fopen("Produto.dat","wb+");
    if(*ANotaComp == NULL)
        *ANotaComp = fopen("NotaCompra.dat","wb+");
    if(*AINotaComp == NULL)
        *AINotaComp = fopen("ItemNotaCompra.dat","wb+");
    if(*AHistPre == NULL)
        *AHistPre = fopen("HistoricoPreco.dat","wb+");
}
//Fecha todo os arquivos
void fecharArquivos(FILE **ACli, FILE **AVend, FILE **AForn, FILE **ANota, FILE **AINota, FILE **AProd,
                    FILE **ANotaComp, FILE **AINotaComp, FILE **AHistPre){

    fclose(*ACli);
    fclose(*AVend);
    fclose(*AForn);
    fclose(*ANota);
    fclose(*AINota);
    fclose(*AProd);
    fclose(*ANotaComp);
    fclose(*AINotaComp);
    fclose(*AHistPre);
}
//Verifica a autenticidade de um CPF
int verificaCPF(char cpf[]){

    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0; //Se o CPF tiver mais ou menos digitos que o necessario, CPF Inválido
    else
        if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
            return 0; //se o CPF tiver todos os números iguais ele é inválido.
        else{
            //digito 1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) //multiplica os números de 10 a 2 e soma os resultados dentro de digito1
                digito1 += (cpf[i]-48) * j;
            digito1 %= 11;
            if(digito1 < 2)
                digito1 = 0;
            else
                digito1 = 11 - digito1;

            if((cpf[9]-48) != digito1)
                return 0; // se o primeiro digito não for o mesmo da validação, CPF Inválido
            else{
                //digito 2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
                digito2 %= 11;
                if(digito2 < 2)
                    digito2 = 0;
                else
                    digito2 = 11 - digito2;

                if((cpf[10]-48) != digito2)
                return 0; // se o segundo digito não for o mesmo da validação, CPF Inválido
            }
        }
    return 1; //CPF Válido
}
//Verifica a autenticidade de um CNPJ
int verificaCNPJ(char cnpj[]){
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cnpj) != 14)
        return 0; //Se o CNPJ tiver mais ou menos digitos que o necessario, CNPJ Inválido
    else
         if((strcmp(cnpj,"00000000000") == 0) || (strcmp(cnpj,"11111111111") == 0) || (strcmp(cnpj,"22222222222") == 0) ||
            (strcmp(cnpj,"33333333333") == 0) || (strcmp(cnpj,"44444444444") == 0) || (strcmp(cnpj,"55555555555") == 0) ||
            (strcmp(cnpj,"66666666666") == 0) || (strcmp(cnpj,"77777777777") == 0) || (strcmp(cnpj,"88888888888") == 0) ||
            (strcmp(cnpj,"99999999999") == 0))
            return 0; //Se o CNPJ tiver todos os números iguais ele é inválido
        else{
            //Verificando Digito 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~
            for(i=0,j=5; i<=3; i++,j--)
                digito1 += cnpj[i] * j;
            for(i=4,j=9; i<=12; i++,j--)
                digito1 += cnpj[i] * j;
            digito1 %= 11;
            if((digito1==0) || (digito1==1)) //Se o digito encontrado for 0 ou 1, ele passa a ser 0,
                digito1 == 0;                //caso contrario, ele é subtraido de 11, o resultado é o
            else                             //valor do primeiro digito. Assim repetindo para o digito2.
                digito1 = 11-digito1;
            if(digito1=cnpj[12]){ //verificando se o primeiro digito é válido
                //Verificando Digito 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~
                for(i=0,j=6; i<=4; i++,j--)
                    digito2 += cnpj[i] * j;
                for(i=5,j=9; i<=13; i++, j--)
                    digito2 += cnpj[i]  * j;
                digito2 %= 11;
                if((digito2==0) || (digito2==1))
                    digito2 == 0;
                else
                    digito2 = 11-digito2;
                if(digito2=cnpj[13])
                    return 1; //Após as duas verificações positivas, retorna 1, CNPJ Válido
                return 0; //Retorna 0 se o segundo digito for inválido
            }
            else
                return 0; //Retorna 0 se o primeiro digito for inválido
        }
    return 1; //CNPJ Válido
}
//Valida uma data fornecida
int verificaData(char data[]){
    int dia, mes, ano;

    sscanf(data,"%d%*c%d%*c%d",&dia,&mes,&ano);
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1960 && ano <= 2020)){	 //verifica se os numeros sao validos
		if(ano == 1960)
			if (dia <= 20 && mes <= 6) //verifica a data mínimima que é 20/06/1960
				return 0;
		if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano é bissexto
            return 1;
        if (dia <= 28 && mes == 2) //verifica o mês de fevereiro
            return 1;
        if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11))//verifica os meses de 30 dias
            return 1;
        if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)){ //verifica os meses de 31 dias
            return 1;
        }else
            return 0;
    }
    return 0;
}
//Converse todo texto para maiusculo
void conversorTexto(char string[]){
    int i = 0;
    do{
        string[i] = toupper(string[i]);
        i++;
    }while(string[i]!= '\0');
}
//Retirar o "/n" "enter" da string
void retiraEnter(char string[]){
	int tamanho = strlen(string) - 1;
	if (string[tamanho] == '\n') {
		string[tamanho] = '\0';
	}else {
		while (getc(stdin) != '\n')
			continue;
	}
}
