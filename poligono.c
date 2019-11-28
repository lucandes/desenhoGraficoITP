#include "poligono.h"

/****************************************************
Função: criarPoligono
Parâmetros: int número de faces do poligono, vetor tipo Ponto, tipo Cor
Retorno: estrutura Polígono

Descrição: gera uma estrutura de polígono, atribui as informações
do polígono e retorna a estrutura.
*****************************************************/
void criarPoligono(int numFaces, Ponto *pontos, Imagem *imagem){
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

		pol.linhas[i-1] = criarLinha(p, imagem->cor, imagem);
	}

	/* criando uma linha do ultimo ponto ao primeiro */
	p[0] = pontos[numFaces - 1];
	p[1] = pontos[0];
	pol.linhas[i - 1] = criarLinha(p, imagem->cor, imagem);

	int n = imagem->desenho.numPoligonos++;
	imagem->desenho.poligonos[n] = pol;
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

/****************************************************
Função: gerarPontosRet
Parâmetros: ponto inicial do retângulo, vetor de pontos, dimensões do retângulo
Retorno: nenhum

Descrição: atribui os pontos do retângulo ao vetor de pontos com base
no ponto inicial e dimensões informadas pelo usuário.
*****************************************************/
void gerarPontosRet(Ponto pontoInicial, Ponto pontos[4], int dim[2]){
	int distX = dim[0];
	int distY = dim[1];

	pontos[0] = pontoInicial;

	pontos[1] = pontos[0];
	pontos[1].x += distX;

	pontos[2] = pontos[1];
	pontos[2].y += distY;

	pontos[3] = pontos[0];
	pontos[3].y += distY;
}