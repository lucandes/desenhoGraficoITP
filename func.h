#ifndef DEFAULT_H
#define DEFAULT_H

#include "struct.h"
#include "imagem.h"
#include "linha.h"
#include "safestdlib.h"
#include "func.h"

Cor criarCor(void);
void pintarPixel(int x, int y, Pixel **pixels, Cor cor);
void liberarAD(Imagem *imagem, Pixel **pixels);
void limparBuffer(void);
void limparFileBuffer(FILE *arq);
void limpaConsole(void);
FILE *lerArquivo(int *temArquivo, Imagem imagem);
int lerDoArquivo(FILE *arquivo, char *entrada);
void executar(char entrada[10], Imagem *imagem, int imagemAberta, int temArquivo, FILE *arqEspecificacao);

#endif