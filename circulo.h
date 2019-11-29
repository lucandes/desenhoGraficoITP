#ifndef CIRCULO_H
#define CIRCULO_H

#include "struct.h"

Circulo criarCirculo(Ponto centro, int raio, Cor cor, Imagem *imagem);
void plot_point(Circulo c, int x, int y, Imagem *imagem, Cor cor);
void inserirCirculo(Circulo c, Imagem *imagem);
void editarCirculo(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao);
int moverCirculo(int dnum, int dist[2], Imagem *imagem);
int copiarCirculo(int dnum, Imagem *imagem);
int removerCirculo(int dnum, Imagem *imagem);

#endif