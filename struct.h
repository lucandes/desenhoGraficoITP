#include <stdio.h>

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct pixel {
	int r,g,b;
}Pixel;

typedef struct ponto {
	int x, y;
}Ponto;

typedef struct imagem {
	FILE *arquivo;
	char nomeDoArquivo[30];
	
	char id[3];
	int lar, alt;
	int max;
	int numDePixels;

	Pixel **pixels;
}Imagem;

#endif