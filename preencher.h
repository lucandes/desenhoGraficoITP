#ifndef PREENCHER_H
#define PREENCHER_H

#include "struct.h"

Preencher criarPreenchimento(Ponto p, Cor novaCor, Imagem *imagem);
void inserirPreenchimento(int x, int y, Preencher p, Imagem *imagem);
void editarPreencher(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao);
int moverPreencher(int dnum, int dist[2], Imagem *imagem);
int copiarPreencher(int dnum, Imagem *imagem);
int removerPreencher(int dnum, Imagem *imagem);

#endif