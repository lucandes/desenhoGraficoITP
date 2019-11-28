#include "struct.h"

/****************************************************
Função: criarCor
Parâmetros: nenhum
Retorno: tipo Cor

Descrição: cria uma cor com valores RGB informados pelo usuário
*****************************************************/
Cor criarCor(int temArquivo, FILE *arq){
	Cor cor;
	int r,g,b;

	if (!temArquivo)
		scanf(" %d %d %d", &r, &g, &b);
	else {
		fscanf(arq, " %d %d %d", &r, &g, &b);
		printf(" %d %d %d", r, g, b);
	}

	cor.r = r;
	cor.g = g;
	cor.b = b;

	return cor;
}

/****************************************************
Função: pintarPixel
Parâmetros: coordenadas do pixel, matriz tipo Cor, cor tipo Cor
Retorno: nenhum

Descrição: altera a cor do pixel na matriz
*****************************************************/
void pintarPixel(int x, int y, Imagem *imagem, Cor cor){
	int maxX = imagem->lar - 1;
	int maxY = imagem->alt - 1;

	/* se o pixel a ser modificado não existir na imagem a função encerrará */
	if (x > maxX || y > maxY || x < 0 || y < 0)
		return;

	// invertido pois a matriz foi inicializada a partir da altura
	imagem->pixels[y][x].r = cor.r;
	imagem->pixels[y][x].g = cor.g;
	imagem->pixels[y][x].b = cor.b;
}