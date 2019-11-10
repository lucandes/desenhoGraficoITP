#include "linha.h"
#include "struct.h"

/****************************************************
Função: criarLinha
Parâmetros: ponteiro tipo Imagem
Retorno: nenhum

Descrição: recebe os pontos do usuário e caso sejam válidos, 
cria uma linha e armazena na estrutura de desenhos da imagem
*****************************************************/
void criarLinha(Imagem *imagem){
	Linha linha;
	scanf("%d %d %d %d", 
		&linha.inicio.x, 
		&linha.inicio.y,
		&linha.fim.x,
		&linha.fim.y);

	int maxX = imagem->lar - 1;
	int maxY = imagem->alt - 1;

	/* se alguma entrada ultrapassa as dimensões da imagem */
	if (linha.inicio.x > maxX || linha.fim.x > maxX ||
		linha.inicio.y > maxY || linha.fim.y > maxY){
		printf("Erro: coordenada invalida inserida\n");
		return;
	}

	/* adicionando linha à estrutura linha */
	imagem->desenho.linhas[imagem->desenho.numLinhas] = linha;
	imagem->desenho.numLinhas += 1;
}

/****************************************************
Função: pintarPixel
Parâmetros: coordenadas do pixel, matriz tipo Pixel, cor tipo Cor
Retorno: nenhum

Descrição: altera a cor do pixel na matriz
*****************************************************/
void pintarPixel(int x, int y, Pixel **pixels, Cor cor){
	// invertido pois a matriz foi inicializada a partir da altura
	pixels[y][x].r = cor.r;
	pixels[y][x].g = cor.g;
	pixels[y][x].b = cor.b;
}	

/****************************************************
Função: inserirLinha
Parâmetros: tipo Linha, ponteiro tipo Imagem
Retorno: nenhum

Descrição: insere a linha na matriz de pixels da imagem,
essa função deve ser executada apenas na etapa de salvamento
da imagem
*****************************************************/
void inserirLinha(Linha linha, Imagem *imagem){
	int x1 = linha.inicio.x;
	int y1 = linha.inicio.y;

	int x2 = linha.fim.x;
	int y2 = linha.fim.y;

	float vx = (float) (x2 - x1) / (y2 - y1);
	if (vx < 0) vx *= -1;
	float vy = (float) (y2 - y1) / (x2 - x1);
	if (vy < 0) vy *= -1;

	float sumx = vx;
	float sumy = vy;

	int countx = x1 < x2 ? 1 : -1;
	int county = y1 < y2 ? 1 : -1;

	while (x1 != x2 || y1 != y2){
		pintarPixel(x1, y1, imagem->pixels, imagem->cor);

		sumx += vx;
		sumy += vy;

		if (sumx >= 1){
			sumx -= 1;
			x1 += countx;
		}

		if (sumy >= 1){
			sumy -= 1;
			y1 += county;
		}
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
}