#include "circulo.h"

/****************************************************
Função: criarCirculo
Parâmetros: ponto central do círculo, inteiro raio, cor
Retorno: tipo Circulo

Descrição: gera um círculo a partir dos parâmetros recebidos e o retorna
*****************************************************/
Circulo criarCirculo(Ponto centro, int raio, Cor cor, Imagem *imagem){
	Circulo c;
	c.centro = centro;
	c.raio = raio;
	c.cor = cor;

	/* adicionando aos desenhos da imagem */
	int n = imagem->desenho.numCirculos++;
	imagem->desenho.circulos[n] = c;
}

/****************************************************
Função: inserirPonto
Parâmetros: tipo Circulo, inteiro x, inteiro y, ponteiro tipo Imagem, tipo Cor
Retorno: nenhum

Descrição: insere um pixel em cada octeto do círculo utilizando o raio 
do círculo e as coordenadas do ponto.
*****************************************************/
void inserirOcteto(Circulo circ, int x, int y, Imagem *imagem, Cor cor){
	int xc = circ.centro.x;
	int yc = circ.centro.y;

	/* em cada octeto do círculo será pintado um píxel */
	pintarPixel(xc + x, yc + y, imagem, cor);
	pintarPixel(xc + x, yc - y, imagem, cor);
	pintarPixel(xc + y, yc + x, imagem, cor);
	pintarPixel(xc + y, yc - x, imagem, cor);
	pintarPixel(xc - x, yc - y, imagem, cor);
	pintarPixel(xc - y, yc - x, imagem, cor);
	pintarPixel(xc - x, yc + y, imagem, cor);
	pintarPixel(xc - y, yc + x, imagem, cor);
}

/****************************************************
Função: inserirCirculo
Parâmetros: tipo Circulo, ponteiro tipo Imagem
Retorno: nenhum

Descrição: insere um circulo na matriz de pixels da imagem
*****************************************************/
void inserirCirculo(Circulo circ, Imagem *imagem){
	int x = 0;
	int y = circ.raio;
  	float pk = (5.0/4.0) - y;

  	/* insere o ponto inicial em cada octeto */
	inserirOcteto(circ, x, y, imagem, circ.cor);

	/* enquanto x for menor que y */
	while(x < y) {
		x++;

		if(pk < 0)
		  pk = pk + 2 * x + 1;

		else {
		  y = y - 1;
		  pk = pk + 2*(x - y) + 1;
		}

	inserirOcteto(circ, x, y, imagem, circ.cor);
	}
}