#ifndef POLIGONO_H
#define POLIGONO_H

#include "struct.h"
#include "linha.h"

Poligono criarPoligono(int numFaces, Ponto *pontos, Imagem *imagem);
void inserirPoligono(Poligono pol, Imagem *imagem);
void gerarPontosRet(Ponto pontoInicial, Ponto pontos[4], int dim[2]);


#endif