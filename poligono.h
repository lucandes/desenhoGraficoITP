#ifndef POLIGONO_H
#define POLIGONO_H

#include "struct.h"
#include "linha.h"

Poligono criarPoligono(int numFaces, Ponto *pontos, Cor cor);
void inserirPoligono(Poligono pol, Imagem *imagem);


#endif