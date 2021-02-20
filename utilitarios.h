#ifndef UTILITARIOS_H_INCLUDED
#define UTILITARIOS_H_INCLUDED

void abrirArquivos(FILE **, FILE **, FILE **, FILE **, FILE **, FILE **, FILE **, FILE **, FILE **);
void fecharArquivos(FILE **, FILE **, FILE **, FILE **, FILE **, FILE **, FILE **, FILE **, FILE **);
int verificaCPF(char []);
int verificaCNPJ(char []);
int verificaData(char []);
void conversorTexto(char []);
void retiraEnter(char []);
void removerNovaLinha(char *);
void checarLinha(char *);

#endif // UTILITARIOS_H_INCLUDED
