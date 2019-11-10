#include "struct.h"

#ifndef LINHA_H
#define LINHA_H

void criarLinha(Imagem *imagem);
void pintarPixel(int x, int y, Pixel **pixels, Cor cor);
void inserirLinha(Linha linha, Imagem *imagem);

#endif