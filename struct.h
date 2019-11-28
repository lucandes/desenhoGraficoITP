#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

/*********************
Estrutura: Poligono
Descrição: armazena informações sobre polígonos na imagem
*********************/
typedef struct poligono{
	int numFaces;
	Ponto pontos[100];
	Linha linhas[100];
}Poligono;

/*********************
Estrutura: Circulo
Descrição: armazena informações sobre círculos na imagem
*********************/
typedef struct circulo{
	Ponto centro;
	int raio;
	Cor cor;
}Circulo;

/*********************
Estrutura: Circulo
Descrição: armazena informações sobre preenchimentos na imagem
*********************/
typedef struct preencher{
	Ponto ponto;
	Cor cor; // cor inicial
	Cor novaCor; // cor a ser inserida
}Preencher;

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

	Circulo circulos[100];
	int numCirculos;

	Preencher preencher[100];
	int numPreencher;
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

	Cor **pixels;
	Cor cor;
	Desenho desenho;
}Imagem;

Cor criarCor(int temArquivo, FILE *arq);
void pintarPixel(int x, int y, Imagem *imagem, Cor cor);

#endif