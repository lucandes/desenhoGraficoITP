#include "poligono.h"
#include <stdlib.h>

Poligono criarPoligono(int numFaces, Ponto *pontos, Cor cor){
	Poligono pol;
	pol.numFaces = numFaces;
	pol.linhas = (Linha *) malloc(numFaces * sizeof(Linha));
	pol.pontos = (Ponto *) malloc(numFaces * sizeof(Ponto));
	for (int i = 0; i < numFaces; pol.pontos[i] = pontos[i++]);
	

	/* criando linhas do polígono */
	for (int i = 1; i < numFaces; ++i){
		pol.linhas[i-1] = (Linha) criarLinha(pontos[i-1], pontos[i], cor);

		// se for a última chamada do loop
		if (i == numFaces - 1)
			// gere uma linha do ultimo ponto ao primeiro
			pol.linhas[i] = (Linha) criarLinha(pontos[i], pontos[0], cor);
	}

	return pol;
}

void inserirPoligono(Poligono pol, Imagem *imagem){
	for (int i = 0; i < pol.numFaces; ++i)
		inserirLinha(pol.linhas[i], imagem);
}