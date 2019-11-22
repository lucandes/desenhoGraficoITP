#include "circulo.h"
#include "func.h"

Circulo criarCirculo(Ponto centro, int raio, Cor cor){
	Circulo c;
	c.centro = centro;
	c.raio = raio;
	c.cor = cor;

	return c;
}

// Plot eight points using circle's symmetrical property
void plot_point(Circulo c, int x, int y, Imagem *imagem, Cor cor){
	int xc = c.centro.x;
	int yc = c.centro.y;

	pintarPixel(xc+x, yc+y, imagem->pixels, cor);
	pintarPixel(xc+x, yc-y, imagem->pixels, cor);
	pintarPixel(xc+y, yc+x, imagem->pixels, cor);
	pintarPixel(xc+y, yc-x, imagem->pixels, cor);
	pintarPixel(xc-x, yc-y, imagem->pixels, cor);
	pintarPixel(xc-y, yc-x, imagem->pixels, cor);
	pintarPixel(xc-x, yc+y, imagem->pixels, cor);
	pintarPixel(xc-y, yc+x, imagem->pixels, cor);
}

void inserirCirculo(Circulo c, Imagem *imagem){
	int x = 0;
	int y = c.raio;
  	float pk = (5.0/4.0) - y;

	/* Plot the points */
	/* Plot the first point */
	plot_point(c, x, y, imagem, c.cor);

	/* Find all vertices till x = y */
	while(x < y) {
		x = x + 1;

		if(pk < 0)
		  pk = pk + 2 * x + 1;

		else {
		  y = y - 1;
		  pk = pk + 2*(x - y) + 1;
		}

	plot_point(c, x, y, imagem, c.cor);

	}
}