#ifndef LINHA_H
#define LINHA_H

#include "struct.h"
#include "func.h"

Linha criarLinha(Ponto pontos[2], Cor cor, Imagem *imagem);
void lerLinha(int temArquivo, FILE *arqEspecificacao, Imagem *imagem);
void inserirLinha(Linha linha, Imagem *imagem);
void editarLinha(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao);
int moverLinha(int dnum, int dist[2], Imagem *imagem);
int copiarLinha(int dnum, Imagem *imagem);
int removerLinha(int dnum, Imagem *imagem);

#endif