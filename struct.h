#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*********************
Estrutura: Pixel
Descrição: armazena as informações sobre o pixel
*********************/
typedef struct pixel {
	int r,g,b;
}Pixel;

/*********************
Estrutura: Cor
Descrição: armazena cores no formato RGB
*********************/
typedef struct cor {
	int r,g,b;
}Cor;

/*********************
Estrutura: Ponto
Descrição: armazena informações sobre pontos na imagem
*********************/
typedef struct ponto {
	int x, y;
}Ponto;

/*********************
Estrutura: Linha
Descrição: armazena informações sobre linhas na imagem
*********************/
typedef struct linha {
	Ponto inicio;
	Ponto fim;
	Cor cor;
}Linha;

typedef struct poligono{
	int numFaces;
	Ponto pontos[100];
	Linha linhas[100];
}Poligono;

/*********************
Estrutura: Desenho
Descrição: Todo desenho feito no programa será armazenado
nessa estrutura, tornando sua manipulação mais eficiente
*********************/
typedef struct desenho {
	Linha linhas[100];
	int numLinhas;

	Poligono poligonos[100];
	int numPoligonos;
}Desenho;

/*********************
Estrutura: Imagem
Descrição: armazena informações sobre a imagem aberta
*********************/
typedef struct imagem {
	FILE *arquivo;
	char nomeDoArquivo[50];
	char caminho[100];
	
	char id[3];
	int lar, alt;
	int max;
	int numDePixels;

	Pixel **pixels;
	Cor cor;
	Desenho desenho;
}Imagem;

#endif