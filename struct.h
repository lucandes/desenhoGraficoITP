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
typedef struct {
	Ponto inicio;
	Ponto fim;
	Cor cor;
}Linha;

/*********************
Estrutura: Desenho
Descrição: Todo desenho feito no programa será armazenado
nessa estrutura, tornando sua manipulação mais eficiente
*********************/
typedef struct desenho {
	Linha linhas[100];

	int numLinhas;
}Desenho;

/*********************
Estrutura: Imagem
Descrição: armazena informações sobre a imagem aberta
*********************/
typedef struct imagem {
	FILE *arquivo;
	char nomeDoArquivo[50];
	
	char id[3];
	int lar, alt;
	int max;
	int numDePixels;

	Pixel **pixels;
	Cor cor;
	Desenho desenho;
}Imagem;

/* funções referentes as estruturas declaradas */


#endif