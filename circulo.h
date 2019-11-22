#include "struct.h"

#ifndef CIRCULO_H
#define CIRCULO_H

Circulo criarCirculo(Ponto centro, int raio, Cor cor);
void plot_point(Circulo c, int x, int y, Imagem *imagem, Cor cor);
void inserirCirculo(Circulo c, Imagem *imagem);


#endif