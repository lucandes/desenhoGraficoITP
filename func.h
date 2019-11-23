#ifndef DEFAULT_H
#define DEFAULT_H

#include "struct.h"
#include "imagem.h"
#include "linha.h"
#include "safestdlib.h"
#include "func.h"

Cor criarCor(int temArquivo, FILE *arq);
void pintarPixel(int x, int y, Imagem *imagem, Cor cor);
void liberarAD(Imagem *imagem, Cor **pixels);
void limparBuffer(void);
void limparFileBuffer(FILE *arq);
void limpaConsole(void);
FILE *lerArquivo(int *temArquivo, Imagem imagem);
int lerDoArquivo(FILE *arquivo, char *entrada);
int checaImagem(int imagemAberta, int temArquivo, FILE *arq);
void lerInteiros(int *inteiros, int numInteiros, int temArquivo, FILE *arq);
void lerPontos(Ponto *pontos, int numPontos, int temArquivo, FILE *arq);
int verificaCoordenadas(int x, int y, Imagem *imagem);
void executar(char entrada[10], Imagem *imagem, int imagemAberta, int temArquivo, FILE *arqEspecificacao);

#endif