#include "struct.h"

#ifndef LINHA_H
#define LINHA_H

void criarLinha(Imagem *imagem);
void pintarPixel(int x, int y, Pixel **pixels, Cor cor);
void inserirLinha(Linha linha, Imagem *imagem);

#endif

/*
	int x1 = linha.inicio.x;
	int y1 = linha.inicio.y;

	int x2 = linha.fim.x;
	int y2 = linha.fim.y;

	float m = (float) (y2 - y1) / (x2 - x1);
	float b = (float) -(x1 * m) * -y1;

	while(x1 != x2 && y1 != y2){
		
	}


	Cor verde;
	verde.r = 0;
	verde.g = 200;
	verde.b = 0;

	Cor verm;
	verm.r = 200;
	verm.g = 0;
	verm.b = 0;

	pintarPixel(linha.inicio.x, linha.inicio.y, imagem->pixels, verde);
	pintarPixel(linha.fim.x, linha.fim.y, imagem->pixels, verm);

*/