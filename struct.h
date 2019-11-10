#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*********************
Estrutura: Pixel
Descrição: representa os pixels da imagem
*********************/
typedef struct pixel {
	int r,g,b;
}Pixel;

/*********************
Estrutura: Cor
Descrição: representa cores no formato RGB
*********************/
typedef struct cor {
	int r,g,b;
}Cor;

/*********************
Estrutura: Ponto
Descrição: guardam informações sobre pontos na imagem
*********************/
typedef struct ponto {
	int x, y;
}Ponto;

/*********************
Estrutura: Linha
Descrição: guardam informações sobre linhas na imagem
*********************/
typedef struct {
	Ponto inicio;
	Ponto fim;
}Linha;

/*********************
Estrutura: Desenho
Descrição: Todo desenho feito no programa será representado
dentro dessa estrutura, tornando sua manipulação mais eficiente
*********************/
typedef struct desenho {
	Linha linhas[100];

	int numLinhas;
}Desenho;

/*********************
Estrutura: Imagem
Descrição: responsável por armazenar toda informação sobre a imagem aberta
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
Desenho criaDesenho(void);
void listarDesenhos(Desenho d);
void inserirDesenhos(Imagem *imagem);
Cor criarCor(void);
Imagem criarImagem(void);
void salvarImagem(Imagem *imagem);

#endif