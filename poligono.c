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
	for (int i = 0; i < numFaces; i++)
		pol.pontos[i] = pontos[i];
	

	/* criando linhas do polígono */
	for (int i = 1; i < numFaces; ++i){
		pol.linhas[i-1] = (Linha) criarLinha(pontos[i-1], pontos[i], cor);

		// se for a última chamada do loop
		if (i == numFaces - 1){
			// gere uma linha do ultimo ponto ao primeiro
			pol.linhas[i] = (Linha) criarLinha(pontos[i], pontos[0], cor);
		}
	}

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