#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct pixel {
	int r,g,b;
}Pixel;

typedef struct cor {
	int r,g,b;
}Cor;

typedef struct ponto {
	int x, y;
}Ponto;

typedef struct {
	Ponto inicio;
	Ponto fim;
}Linha;

typedef struct desenho {
	Linha linhas[100];

	int numLinhas;
}Desenho;

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

Desenho criaDesenho(void);
void listarDesenhos(Desenho d);
void inserirDesenhos(Imagem *imagem);
Imagem criarImagem(void);
void salvarImagem(Imagem *imagem);
Cor criarCor(void);

#endif