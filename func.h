#ifndef DEFAULT_H
#define DEFAULT_H

#include <stdio.h>
#include <string.h>

#include "struct.h"
#include "imagem.h"
#include "linha.h"
#include "circulo.h"
#include "poligono.h"

void printAjuda(int temArquivo);
void liberarAD(Imagem *imagem, Cor **pixels);
void limparBuffer(int temArquivo, FILE *arq);
void limpaConsole(void);
FILE *novoArquivo(int *temArquivo, Imagem imagem);
int lerArquivo(FILE *arquivo, char *entrada);
int verificaCoordenadas(int x, int y, Imagem *imagem);

#endif