#include "poligono.h"
#include "safestdlib.h"

/****************************************************
Função: criarPoligono
Parâmetros: int número de faces do poligono, vetor tipo Ponto, tipo Cor
Retorno: estrutura Polígono

Descrição: gera uma estrutura de polígono, atribui as informações
do polígono e retorna a estrutura.
*****************************************************/
Poligono criarPoligono(int numFaces, Ponto *pontos, Cor cor){
	Poligono pol;
	pol.numFaces = numFaces; 

	Ponto p[2]; // vetor utilizado para gerar linhas
	int i; // contador

	/* atribuindo os pontos à estrutura do poligono */
	for (int i = 0; i < numFaces; i++)
		pol.pontos[i] = pontos[i];

	/* criando linhas do polígono */
	for (i = 1; i < numFaces; ++i){
		p[0] = pontos[i - 1];
		p[1] = pontos[i];

		pol.linhas[i-1] = criarLinha(p, cor);
	}

	/* criando uma linha do ultimo ponto ao primeiro */
	p[0] = pontos[numFaces - 1];
	p[1] = pontos[0];
	pol.linhas[i] = criarLinha(p, cor);

	return pol;
}

/****************************************************
Função: inserirPoligono
Parâmetros: tipo Poligono, Tipo imagem
Retorno: nenhum

Descrição: insere na imagem todos os polígonos criados
*****************************************************/
void inserirPoligono(Poligono pol, Imagem *imagem){
	/* inserindo todas as linhas do polígono na imagem */
	for (int i = 0; i < pol.numFaces; ++i)
		inserirLinha(pol.linhas[i], imagem);
}