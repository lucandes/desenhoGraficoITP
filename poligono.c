#include "poligono.h"

/****************************************************
Função: criarPoligono
Parâmetros: int número de faces do poligono, vetor tipo Ponto, tipo Cor
Retorno: estrutura Polígono

Descrição: gera uma estrutura de polígono, atribui as informações
do polígono e retorna a estrutura.
*****************************************************/
Poligono criarPoligono(int numFaces, Ponto *pontos, Imagem *imagem){
	Poligono pol;
	pol.numFaces = numFaces;
	pol.cor = imagem->cor;

	/* atribuindo os pontos à estrutura do poligono */
	for (int i = 0; i < numFaces; i++)
		pol.pontos[i] = pontos[i];

	return pol;
}

/****************************************************
Função: inserirPoligono
Parâmetros: tipo Poligono, Tipo imagem
Retorno: nenhum

Descrição: insere na imagem todos os polígonos criados
*****************************************************/
void inserirPoligono(Poligono pol, Imagem *imagem){
	Ponto p[2]; // vetor utilizado para gerar linhas
	int i; // contador

	/* criando linhas do polígono */
	for (i = 1; i < pol.numFaces; ++i){
		p[0] = pol.pontos[i - 1];
		p[1] = pol.pontos[i];

		pol.linhas[i-1] = criarLinha(p, pol.cor, imagem);
	}

	/* criando uma linha do ultimo ponto ao primeiro */
	p[0] = pol.pontos[pol.numFaces - 1];
	p[1] = pol.pontos[0];
	pol.linhas[i - 1] = criarLinha(p, pol.cor, imagem);

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

void editarRetangulo(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao){
	/* verifica se o poligono existe */
	if (dnum < 1 || dnum > imagem->desenho.numPoligonos){
		printf("Erro: o desenho selecionado nao existe\n");
		limparBuffer(temArquivo, arqEspecificacao);
		return;
	}

	/**** mesmo código de criar linha da função "executar" ****/
	Ponto pontoInicial;
	lerPontos(&pontoInicial, 1, temArquivo, arqEspecificacao);
	int dimensoes[2];
	lerInteiros(dimensoes, 2, temArquivo, arqEspecificacao);


	int numFaces = 4;
	Ponto pontos[numFaces];
	gerarPontosRet(pontoInicial, pontos, dimensoes);
	/******************** fim do código ***********************/

	
	Poligono pol = criarPoligono(numFaces, pontos, imagem);
	imagem->desenho.poligonos[dnum - 1] = pol;
}

void editarPoligono(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao){
	/* verifica se o poligono existe */
	if (dnum < 1 || dnum > imagem->desenho.numPoligonos){
		printf("Erro: o desenho selecionado nao existe\n");
		return;
	}

	int numFaces; 
	lerInteiros(&numFaces, 1, temArquivo, arqEspecificacao);

	/**** mesmo código de criar linha da função "executar" ****/
	if (numFaces < 3 || numFaces > 100){
		printf("Erro: numero inválido de faces inserido\n");
		return;
	}

	Ponto pontos[numFaces];
	lerPontos(pontos, numFaces, temArquivo, arqEspecificacao);
	/******************** fim do código ***********************/

	Poligono pol = criarPoligono(numFaces, pontos, imagem);
	imagem->desenho.poligonos[dnum - 1] = pol;
}

int moverPoligono(int dnum, int dist[2], Imagem *imagem){
	/* verifica se o poligono existe */
	if (dnum < 1 || dnum > imagem->desenho.numPoligonos){
		printf("Erro: o desenho selecionado nao existe\n");
		return 0;
	}

	Poligono new = imagem->desenho.poligonos[dnum - 1];
	new.cor = imagem->cor;

	/* inserindo deslocamento no retangulo */
	for (int i = 0; i < new.numFaces; i++){
		new.pontos[i].x += dist[0];
		new.pontos[i].y += dist[1];
	}

	imagem->desenho.poligonos[dnum - 1] = new;

	return 1;
}

int copiarPoligono(int dnum, Imagem *imagem){
	/* verifica se o poligono existe */
	if (dnum < 1 || dnum > imagem->desenho.numPoligonos){
		printf("Erro: o desenho selecionado nao existe\n");
		return 0;
	}

	Poligono new = imagem->desenho.poligonos[dnum - 1];
	int n = imagem->desenho.numPoligonos++;
	imagem->desenho.poligonos[n] = new;

	int numOrdem = imagem->desenho.numOrdem++;
	imagem->desenho.ordem[numOrdem] = 2;

	return 1;
}

int removerPoligono(int dnum, Imagem *imagem){
	Desenho *d = &imagem->desenho;

	/* verifica se o poligono existe */
	if (dnum < 1 || dnum > imagem->desenho.numPoligonos)
		return 0;

	/* movendo todas os poligonos seguintes para a casa anterior */
	for (int i = dnum; i < d->numPoligonos; i++)
		d->poligonos[i - 1] = d->poligonos[i];
	d->numPoligonos--;

	int ord = 0; //contador
	int ordIndex;

	/* buscando a posição do desenho removido no vetor de ordem */
	for (int i = 0; ord != dnum; ++i){
		if (d->ordem[i] == 2) // representa poligono
			ord++;
		if (ord == dnum)
			ordIndex = i; // pegando a posição atual do desenho
	}

	/* movendo todas os desenhos seguintes para a casa anterior */
	for (int i = ordIndex; i < d->numOrdem; i++)
		d->ordem[i - 1] = d->ordem[i];
	d->numOrdem--;

	return 1;
}