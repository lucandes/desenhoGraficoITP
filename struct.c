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
	imagem->pixelsCopy[y][x].r = cor.r;
	imagem->pixelsCopy[y][x].g = cor.g;
	imagem->pixelsCopy[y][x].b = cor.b;
}

/****************************************************
Função: lerInteiros
Parâmetros: ponteiro de inteiro, numero de inteiros a serem lidos, inteiro temArquivo, arquivo tipo FILE
Retorno: nenhum

Descrição: lê a quantidade determinada de inteiros e os insere 
no endereço passado por parâmetro, se houver um arquivo de 
especificação a leitura será realizada no arquivo
*****************************************************/
void lerInteiros(int *inteiros, int numInteiros, int temArquivo, FILE *arq){
	for (int i = 0; i < numInteiros; ++i){
		if (!temArquivo)
			scanf(" %d", &inteiros[i]);
		else {
			fscanf(arq, " %d", &inteiros[i]);
			printf(" %d", inteiros[i]);
		}
	}
}

/****************************************************
Função: lerPontos
Parâmetros: ponteiro de ponto, numero de pontos a serem lidos, inteiro temArquivo, arquivo tipo FILE
Retorno: nenhum

Descrição: lê a quantidade determinada de pontos e os insere 
no endereço que foi passado por parâmetro, se houver um arquivo de 
especificação a leitura será realizada nesse arquivo
*****************************************************/
void lerPontos(Ponto *pontos, int numPontos, int temArquivo, FILE *arq){
	for (int i = 0; i < numPontos; ++i){
		if (!temArquivo)
			scanf(" %d %d", &pontos[i].x, &pontos[i].y);
		else {
			fscanf(arq, " %d %d", &pontos[i].x, &pontos[i].y);
			printf(" %d %d", pontos[i].x, pontos[i].y);
		}
	}
}