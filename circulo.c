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

	return c;
}

/****************************************************
Função: lerCirculo
Parâmetros: inteiro temArquivo, arquivo de especificação, ponteiro tipo Imagem
Retorno: nenhum

Descrição: faz a leitura dos paramêtros necessários para a criação
de um novo desenho na imagem, chama a função de criação
*****************************************************/
void lerCirculo(int temArquivo, FILE *arqEspecificacao, Imagem *imagem){
	Ponto centro;
	lerPontos(&centro, 1, temArquivo, arqEspecificacao);

	int raio;
	lerInteiros(&raio, 1, temArquivo, arqEspecificacao);
	limparBuffer(temArquivo, arqEspecificacao);

	Circulo c = criarCirculo(centro, raio, imagem->cor, imagem);

	/* adicionando aos desenhos da imagem */
	int n = imagem->desenho.numCirculos++;
	imagem->desenho.circulos[n] = c;

	/* adicionando o circulo a ordem */
	int i = imagem->desenho.numOrdem++;
	imagem->desenho.ordem[i] = 3; // 3 representa círculos
}

/****************************************************
Função: inserir
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

Descrição: insere um circulo na matriz de pixels da imagem.
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

/****************************************************
Função: editarCirculo
Parâmetros: numero do desenho, ponteiro tipo Imagem, inteiro temArquivo, arquivo de especificação
Retorno: nenhum

Descrição: permite que o usuário reescreva as informações de
um determinado desenho.
*****************************************************/
void editarCirculo(int dnum, Imagem *imagem, int temArquivo, FILE *arqEspecificacao){
	/* verifica se o círculo existe */
	if (dnum < 1 || dnum > imagem->desenho.numCirculos){
		printf("Erro: o desenho selecionado nao existe\n");
	}

	/**** mesmo código de criar circulo da função "executar" ****/
	Ponto centro;
	lerPontos(&centro, 1, temArquivo, arqEspecificacao);

	int raio;
	lerInteiros(&raio, 1, temArquivo, arqEspecificacao);
	/******************** fim do código ***********************/

	Circulo c = criarCirculo(centro, raio, imagem->cor, imagem);
	imagem->desenho.circulos[dnum - 1] = c;
}

/****************************************************
Função: moverCirculo
Parâmetros: numero do desenho, vetor distancia do deslocamento, ponteiro tipo Imagem,
Retorno: nenhum

Descrição: permite que o usuário mova um determinado desenho.
*****************************************************/
int moverCirculo(int dnum, int dist[2], Imagem *imagem){
	/* verifica se o círculo existe */
	if (dnum < 1 || dnum > imagem->desenho.numCirculos){
		printf("Erro: o desenho selecionado nao existe\n");
		return 0;
	}

	/* inserindo deslocamento no círculo */
	imagem->desenho.circulos[dnum - 1].centro.x += dist[0];
	imagem->desenho.circulos[dnum - 1].centro.y += dist[1];

	return 1;
}

/****************************************************
Função: copiarCirculo
Parâmetros: numero do desenho, ponteiro tipo Imagem,
Retorno: inteiro que indica se o desenho existe

Descrição: permite que o usuário copie um determinado desenho.
*****************************************************/
int copiarCirculo(int dnum, Imagem *imagem){
	/* verifica se o círculo existe */
	if (dnum < 1 || dnum > imagem->desenho.numCirculos){
		printf("Erro: o desenho selecionado nao existe\n");
		return 0;
	}

	Circulo new = imagem->desenho.circulos[dnum - 1];
	int n = imagem->desenho.numCirculos++;
	imagem->desenho.circulos[n] = new;

	int numOrdem = imagem->desenho.numOrdem++;
	imagem->desenho.ordem[numOrdem] = 3;

	return 1;
}

/****************************************************
Função: removerCirculo
Parâmetros: numero do desenho, ponteiro tipo Imagem,
Retorno: inteiro que indica se o desenho existe

Descrição: permite que o usuário remova um determinado desenho.
*****************************************************/
int removerCirculo(int dnum, Imagem *imagem){
	Desenho *d = &imagem->desenho;

	/* verifica se o círculo existe */
	if (dnum < 1 || dnum > imagem->desenho.numCirculos){
		printf("Erro: o desenho selecionado nao existe\n");
		return 0;
	}

	/* movendo todos os circulos seguintes para a casa anterior */
	for (int i = dnum; i < d->numCirculos; i++)
		d->circulos[i - 1] = d->circulos[i];
	d->numCirculos--;

	int ord = 0; //contador
	int ordIndex;

	/* buscando a posição do desenho removido no vetor de ordem */
	for (int i = 0; i < d->numOrdem; ++i){
		if (d->ordem[i] == 3){ // representa circulo
			ord++;

			if (ord == dnum){
				ordIndex = i; // pegando a posição atual do desenho
				break;
			}
		}
	}

	/* movendo todas os desenhos seguintes para a casa anterior */
	for (int i = ordIndex; i < d->numOrdem; i++){
		d->ordem[i] = d->ordem[i + 1];
	}
	d->numOrdem--;

	return 1;
}