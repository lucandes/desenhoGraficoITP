#ifndef POLIGONO_H
#define POLIGONO_H

#include "struct.h"
#include "linha.h"

Poligono criarPoligono(int numFaces, Ponto *pontos, Imagem *imagem);
void lerRetangulo(int temArquivo, FILE *arqEspecificacao, Imagem *imagem);
void lerPoligono(int temArquivo, FILE *arqEspecificacao, Imagem *imagem);
void inserirPoligono(Poligono pol, Imagem *imagem);
void gerarPontosRet(Ponto pontoInicial, Ponto pontos[4], int dim[2]);
void editarRetangulo(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao);
void editarPoligono(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao);
int moverPoligono(int dnum, int dist[2], Imagem *imagem);
int copiarPoligono(int dnum, Imagem *imagem);
int removerPoligono(int dnum, Imagem *imagem);

#endif