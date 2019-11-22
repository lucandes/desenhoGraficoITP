#include "linha.h"
#include "func.h"

/****************************************************
Função: criarLinha
Parâmetros: ponteiro tipo Imagem
Retorno: nenhum

Descrição: recebe os pontos do usuário e caso sejam válidos, 
cria uma linha e armazena na estrutura de desenhos da imagem
*****************************************************/
Linha criarLinha(Ponto pontos[2], Cor cor){
	Linha linha;

	/* leitura das coordenadas */
	linha.inicio.x = pontos[0].x;
	linha.inicio.y = pontos[0].y;

	linha.fim.x = pontos[1].x;
	linha.fim.y = pontos[1].y;

	linha.cor = cor;
	
	return linha;
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
	/* declarando variaveis */
	int x1 = linha.inicio.x;
	int y1 = linha.inicio.y;

	int x2 = linha.fim.x;
	int y2 = linha.fim.y;

	/* variacao de x e y */
	float vx = (float) (x2 - x1) / (y2 - y1);
	if (vx < 0) vx *= -1;
	float vy = (float) (y2 - y1) / (x2 - x1);
	if (vy < 0) vy *= -1;

	/* determina se um pixel será avançado ou não */
	float sumx = vx;
	float sumy = vy;

	/* determina a direção na qual o pixel irá avançar */
	int countx = x1 < x2 ? 1 : -1;
	int county = y1 < y2 ? 1 : -1;

	/* pinta o pixel inicial */
	pintarPixel(x1, y1, imagem, linha.cor);

	/* enquanto a linha não alcançar o ponto final */
	while (x1 != x2 || y1 != y2){
		sumx += vx;
		sumy += vy;

		// se sumx for maior ou igual a um
		if (sumx >= 1){
			sumx -= 1;
			x1 += countx; //avance um pixel
		}

		// se sumy for maior ou igual a um
		if (sumy >= 1){
			sumy -= 1;
			y1 += county; //avance um pixel
		}

		pintarPixel(x1, y1, imagem, linha.cor);
	}
}