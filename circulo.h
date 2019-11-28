#ifndef CIRCULO_H
#define CIRCULO_H

#include "struct.h"

Circulo criarCirculo(Ponto centro, int raio, Cor cor, Imagem *imagem);
void plot_point(Circulo c, int x, int y, Imagem *imagem, Cor cor);
void inserirCirculo(Circulo c, Imagem *imagem);


#endif